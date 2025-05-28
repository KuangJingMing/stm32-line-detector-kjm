#include "ff.h"     /* FatFs ͷ�ļ� */
#include "diskio.h" /* ���� I/O �ӿ� */
#include <stdio.h>  /* ��׼ I/O������ sprintf */
#include <string.h> /* �ַ������� */
#include "tests.h"
#include "./BSP/W25QXX/w25qxx.h"

void format_fs(void)
{
    FRESULT res;                               /* FatFs ������� */
    MKFS_PARM fmt_parm = {FM_FAT, 0, 0, 0, 0}; /* FAT ��ʽ���� */
    BYTE work[FF_MAX_SS];                      /* ���������� */

    printf("Starting file system format...\r\n");

    /* ��ʽ���ļ�ϵͳ */
    res = f_mkfs("", &fmt_parm, work, sizeof(work));
    if (res != FR_OK)
    {
        printf("f_mkfs failed, error code: %d\r\n", res);
        return;
    }
    printf("File system formatted successfully.\r\n");
}

/* FatFs ���Ժ��� */
void FatFs_Test(void)
{
    FATFS fs;         /* �ļ�ϵͳ���� */
    FIL file;         /* �ļ����� */
    FRESULT res;      /* FatFs ������� */
    char buffer[100]; /* ��д������ */
    UINT bw, br;      /* д��Ͷ�ȡ���ֽ��� */

    /* 1. ���Թ����ļ�ϵͳ */
    res = f_mount(&fs, "", 1); /* ������������"" ��ʾĬ����������1 ��ʾ�������� */
    if (res != FR_OK)
    {
        printf("f_mount failed, error code: %d. Trying to format...\r\n", res);

        /* �������ʧ�ܣ����Ը�ʽ�� */
        format_fs();

        /* ���³��Թ��� */
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
    /* 2. ������д���ļ� */
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

    // ֻ���ļ�����ͬ�������������ļ�ϵͳͬ��
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

    /* 3. ��ȡ�ļ����� */
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

    /* 4. ж���ļ�ϵͳ */
    f_mount(0, "", 0);
    printf("File system unmounted. FatFs test completed successfully!\r\n");

    while (1)
    {
        // ������ɣ�ͣ������
    }
}
