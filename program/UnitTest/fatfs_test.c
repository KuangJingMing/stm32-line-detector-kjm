#include "ff.h"     /* FatFs 头文件 */
#include "diskio.h" /* 磁盘 I/O 接口 */
#include <stdio.h>  /* 标准 I/O，用于 sprintf */
#include <string.h> /* 字符串操作 */
#include "tests.h"
#include "./BSP/W25QXX/w25qxx.h"

void format_fs(void)
{
    FRESULT res;                               /* FatFs 操作结果 */
    MKFS_PARM fmt_parm = {FM_FAT, 0, 0, 0, 0}; /* FAT 格式参数 */
    BYTE work[FF_MAX_SS];                      /* 工作缓冲区 */

    printf("Starting file system format...\r\n");

    /* 格式化文件系统 */
    res = f_mkfs("", &fmt_parm, work, sizeof(work));
    if (res != FR_OK)
    {
        printf("f_mkfs failed, error code: %d\r\n", res);
        return;
    }
    printf("File system formatted successfully.\r\n");
}

/* FatFs 测试函数 */
void FatFs_Test(void)
{
    FATFS fs;         /* 文件系统对象 */
    FIL file;         /* 文件对象 */
    FRESULT res;      /* FatFs 操作结果 */
    char buffer[100]; /* 读写缓冲区 */
    UINT bw, br;      /* 写入和读取的字节数 */

    /* 1. 尝试挂载文件系统 */
    res = f_mount(&fs, "", 1); /* 挂载驱动器，"" 表示默认驱动器，1 表示立即挂载 */
    if (res != FR_OK)
    {
        printf("f_mount failed, error code: %d. Trying to format...\r\n", res);

        /* 如果挂载失败，尝试格式化 */
        format_fs();

        /* 重新尝试挂载 */
        res = f_mount(&fs, "", 1);
        if (res != FR_OK)
        {
            printf("f_mount failed again after format, error code: %d\r\n", res);
            return;
        }
    }
    printf("File system mounted successfully.\r\n");

#define TEST_WRITE 0

#if TEST_WRITE
    /* 2. 创建并写入文件 */
    res = f_open(&file, "test.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK)
    {
        printf("f_open (write) failed, error code: %d\r\n", res);
        f_mount(0, "", 0);
        return;
    }

    strcpy(buffer, "Hello, FatFs! This is a test message.\r\n");
    res = f_write(&file, buffer, strlen(buffer), &bw);
    if (res != FR_OK || bw != strlen(buffer))
    {
        printf("f_write failed, error code: %d, bytes written: %d\r\n", res, bw);
        f_close(&file);
        f_mount(0, "", 0);
        return;
    }
    printf("File written successfully, bytes written: %d\r\n", bw);

    // 只对文件进行同步，不对整个文件系统同步
    res = f_sync(&file);
    if (res != FR_OK)
    {
        printf("f_sync failed, error code: %d\r\n", res);
    }
    else
    {
        printf("File synced successfully.\r\n");
    }

    f_close(&file);
#endif

    /* 3. 读取文件内容 */
    res = f_open(&file, "test.txt", FA_READ);
    if (res != FR_OK)
    {
        printf("f_open (read) failed, error code: %d\r\n", res);
        f_mount(0, "", 0);
        return;
    }

    memset(buffer, 0, sizeof(buffer));
    res = f_read(&file, buffer, sizeof(buffer) - 1, &br);
    if (res != FR_OK)
    {
        printf("f_read failed, error code: %d\r\n", res);
        f_close(&file);
        f_mount(0, "", 0);
        return;
    }
    printf("File read successfully, bytes read: %d\r\n", br);
    printf("Content: %s\r\n", buffer);

    f_close(&file);

    /* 4. 卸载文件系统 */
    f_mount(0, "", 0);
    printf("File system unmounted. FatFs test completed successfully!\r\n");

    while (1)
    {
        // 测试完成，停在这里
    }
}
