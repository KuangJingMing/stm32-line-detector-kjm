/*-----------------------------------------------------------------------*/
/* Low level disk I/O module for FatFs     (C)ChaN, 2019                */
/*-----------------------------------------------------------------------*/

#include "ff.h"         /* Obtains integer types */
#include "diskio.h"     /* Declarations of disk functions */
#include "./BSP/W25QXX/w25qxx.h"
#include "stdio.h"
#include "string.h"
#include "./BSP/RTC/rtc.h"

/* Definitions of physical drive number for each drive */
#define DEV_FLASH   0   /* Map W25QXX flash to physical drive 0 */

/* Sector size for FatFS (标准512字节) */
#define SECTOR_SIZE 512
/* Total number of sectors in W25Q64 (8MB / 512B = 16384 sectors) */
#define TOTAL_SECTORS 16384
/* Physical sector size of W25QXX flash */
#define W25QXX_FLASH_SECTOR_SIZE 4096

static DSTATUS g_disk_status = STA_NOINIT;  /* 磁盘状态 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status(BYTE pdrv)
{
    switch (pdrv) {
    case DEV_FLASH:
        return g_disk_status;
    }
    return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(BYTE pdrv)
{
		static u16 id;
    switch (pdrv) {
    case DEV_FLASH:
        id = W25QXX_ReadID();
     
        if (id == W25Q64) {
            g_disk_status = 0;  /* 初始化成功 */
        } else {
            /* 尝试重新初始化 */
            W25QXX_Init();
            id = W25QXX_ReadID();
            if (id == W25Q64) {
                g_disk_status = 0;
            } else {
                g_disk_status = STA_NOINIT;
            }
        }
        return g_disk_status;
    }
    return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,      /* Physical drive number to identify the drive */
    BYTE *buff,     /* Data buffer to store read data */
    LBA_t sector,   /* Start sector in LBA */
    UINT count      /* Number of sectors to read */
)
{
    switch (pdrv) {
    case DEV_FLASH:

        /* Check for valid sector range */
        if (sector + count > TOTAL_SECTORS) {
            return RES_PARERR;
        }

        /* Calculate physical address */
        u32 addr = sector * SECTOR_SIZE;
        u32 size = count * SECTOR_SIZE;
        
        /* Read data from flash */
        W25QXX_Read(buff, addr, size);
        

        return RES_OK;
    }
    return RES_PARERR;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
    BYTE pdrv,          /* Physical drive number to identify the drive */
    const BYTE *buff,   /* Data to be written */
    LBA_t sector,       /* Start sector in LBA */
    UINT count          /* Number of sectors to write */
)
{
    switch (pdrv) {
    case DEV_FLASH:
        
        /* Check for valid sector range */
        if (sector + count > TOTAL_SECTORS) {
            return RES_PARERR;
        }

        /* Calculate physical address */
        u32 addr = sector * SECTOR_SIZE;
        u32 size = count * SECTOR_SIZE;
        
        /* Write data to flash */
        W25QXX_Write((BYTE *)buff, addr, size);
        
        return RES_OK;
    }
    return RES_PARERR;
}

#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE pdrv,      /* Physical drive number (0..) */
    BYTE cmd,       /* Control code */
    void *buff      /* Buffer to send/receive control data */
)
{
    switch (pdrv) {
    case DEV_FLASH:
        switch (cmd) {
        case CTRL_SYNC:
            /* 确保所有挂起的写操作都已完成 */
            W25QXX_Wait_Busy();
            // 添加额外延时确保数据稳定
            HAL_Delay(10);
            return RES_OK;

        case GET_SECTOR_COUNT:
            /* 返回扇区总数 */
            *(LBA_t *)buff = TOTAL_SECTORS;
            return RES_OK;

        case GET_SECTOR_SIZE:
            /* 返回扇区大小 */
            *(WORD *)buff = SECTOR_SIZE;
            return RES_OK;

        case GET_BLOCK_SIZE:
            /* 返回擦除块大小（以扇区为单位） */
            *(DWORD *)buff = W25QXX_FLASH_SECTOR_SIZE / SECTOR_SIZE;  // 8
            return RES_OK;

        case CTRL_TRIM:
            /* Trim操作 - W25QXX不支持，但返回OK避免错误 */
            return RES_OK;

        default:
            return RES_PARERR;
        }
    }
    return RES_PARERR;
}

/*-----------------------------------------------------------------------*/
/* Get current time for timestamp                                        */
/*-----------------------------------------------------------------------*/

DWORD get_fattime (void)
{
    /* 返回当前时间，格式为FAT文件系统时间戳 */
    /* 格式: bit31:25(年-1980), bit24:21(月), bit20:16(日), bit15:11(时), bit10:5(分), bit4:0(秒/2) */
    
    DWORD time = 0;
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;
    
    HAL_RTC_GetTime(&RTC_Handler, &RTC_TimeStruct, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN);
    
    /* 按照FAT文件系统时间戳格式组装时间 */
    time = ((DWORD)(RTC_DateStruct.Year + 20) << 25)    // 年份(相对于1980年，RTC年份+2000-1980=+20)
         | ((DWORD)RTC_DateStruct.Month << 21)         // 月份(1-12)
         | ((DWORD)RTC_DateStruct.Date << 16)          // 日期(1-31)
         | ((DWORD)RTC_TimeStruct.Hours << 11)         // 小时(0-23)
         | ((DWORD)RTC_TimeStruct.Minutes << 5)        // 分钟(0-59)
         | ((DWORD)RTC_TimeStruct.Seconds >> 1);       // 秒/2(0-29)
    
    return time;
}
