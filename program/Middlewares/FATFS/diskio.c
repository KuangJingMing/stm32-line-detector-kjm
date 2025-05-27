/*-----------------------------------------------------------------------*/
/* Low level disk I/O module for FatFs     (C)ChaN, 2019                */
/*-----------------------------------------------------------------------*/

#include "ff.h"         /* Obtains integer types */
#include "diskio.h"     /* Declarations of disk functions */
#include "./BSP/W25QXX/w25qxx.h"
#include "stdio.h"
#include "string.h"

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
    switch (pdrv) {
    case DEV_FLASH:
        u16 id = W25QXX_ReadID();
        printf("disk_initialize: ReadID = 0x%X\r\n", id);
        
        if (id == W25Q64) {
            g_disk_status = 0;  /* 初始化成功 */
            printf("W25Q64 disk initialized successfully.\r\n");
        } else {
            /* 尝试重新初始化 */
            W25QXX_Init();
            id = W25QXX_ReadID();
            if (id == W25Q64) {
                g_disk_status = 0;
                printf("W25Q64 disk reinitialized successfully.\r\n");
            } else {
                g_disk_status = STA_NOINIT;
                printf("W25Q64 disk initialization failed, ID: 0x%X\r\n", id);
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
        printf("disk_read: sector=%lu, count=%u\r\n", (unsigned long)sector, count);
        
        /* Check for valid sector range */
        if (sector + count > TOTAL_SECTORS) {
            printf("disk_read: Parameter error - sector out of range\r\n");
            return RES_PARERR;
        }

        /* Calculate physical address */
        u32 addr = sector * SECTOR_SIZE;
        u32 size = count * SECTOR_SIZE;
        
        printf("Reading from addr=0x%X, size=%lu\r\n", addr, size);
        
        /* Read data from flash */
        W25QXX_Read(buff, addr, size);
        
        /* 调试：显示引导扇区的前几个字节 */
        if (sector == 0) {
            printf("Boot sector header: ");
            for (int i = 0; i < 16; i++) {
                printf("%02X ", buff[i]);
            }
            printf("\r\n");
        }
        
        printf("disk_read: success\r\n");
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
        printf("disk_write: sector=%lu, count=%u\r\n", (unsigned long)sector, count);
        
        /* Check for valid sector range */
        if (sector + count > TOTAL_SECTORS) {
            printf("disk_write: Parameter error - sector out of range\r\n");
            return RES_PARERR;
        }

        /* Calculate physical address */
        u32 addr = sector * SECTOR_SIZE;
        u32 size = count * SECTOR_SIZE;
        
        printf("Writing to addr=0x%X size=%lu\r\n", addr, size);
        
        /* Write data to flash */
        W25QXX_Write((BYTE *)buff, addr, size);
        
        printf("disk_write: success\r\n");
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
            /* Ensure all pending writes are completed */
            printf("disk_ioctl: CTRL_SYNC\r\n");
            W25QXX_Wait_Busy();
            return RES_OK;

        case GET_SECTOR_COUNT:
            /* Return the total number of sectors */
            printf("disk_ioctl: GET_SECTOR_COUNT = %d\r\n", TOTAL_SECTORS);
            *(LBA_t *)buff = TOTAL_SECTORS;
            return RES_OK;

        case GET_SECTOR_SIZE:
            /* Return the sector size */
            printf("disk_ioctl: GET_SECTOR_SIZE = %d\r\n", SECTOR_SIZE);
            *(WORD *)buff = SECTOR_SIZE;
            return RES_OK;

        case GET_BLOCK_SIZE:
            /* Return the erase block size in sectors */
            printf("disk_ioctl: GET_BLOCK_SIZE = 8\r\n");
            *(DWORD *)buff = W25QXX_FLASH_SECTOR_SIZE / SECTOR_SIZE;  // 4096/512 = 8
            return RES_OK;

        case CTRL_TRIM:
            /* Trim operation - not supported for W25QXX */
            printf("disk_ioctl: CTRL_TRIM - not supported\r\n");
            return RES_OK;  /* 改为OK，避免错误 */

        default:
            printf("disk_ioctl: Unknown command %d\r\n", cmd);
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
    
    /* 示例：2024年1月1日 12:00:00 */
    time |= (DWORD)(2024 - 1980) << 25;  // 年
    time |= (DWORD)1 << 21;              // 月
    time |= (DWORD)1 << 16;              // 日
    time |= (DWORD)12 << 11;             // 时
    time |= (DWORD)0 << 5;               // 分
    time |= (DWORD)0;                    // 秒/2

    return time;
}
