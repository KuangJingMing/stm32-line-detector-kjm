#include "main.h"
#include <stdio.h>
#include <string.h>
#include "ff.h"         /* FatFs ͷ�ļ� */
#include "diskio.h"     /* ���� I/O �ӿ� */

// �ļ�·��
#define RTC_TIME_FILE "rtc_time.txt"

// ���� RTC ʱ�䵽�ļ�
void RTC_SaveTimeToFile(void)
{
    FATFS fs;
    FIL file;
    FRESULT res;
    char buf[50];
    UINT bytesWritten;
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;

    // ��ȡ��ǰʱ�������
    HAL_RTC_GetTime(&RTC_Handler, &RTC_TimeStruct, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN);

    // �����ļ�ϵͳ
    res = f_mount(&fs, "", 1);
    if (res != FR_OK)
    {
        printf("Mount FS Failed: %d\n", res);
        return;
    }

    // ���ļ�����д��ģʽ��
    res = f_open(&file, RTC_TIME_FILE, FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK)
    {
        printf("Open File Failed: %d\n", res);
        f_mount(0, "", 0); // ж���ļ�ϵͳ
        return;
    }

    // ��ʽ��ʱ������Ϊ�ַ���
    sprintf(buf, "20%02d-%02d-%02d %02d:%02d:%02d %d\n",
            RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date,
            RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds,
            RTC_DateStruct.WeekDay);

    // д���ļ�
    res = f_write(&file, buf, strlen(buf), &bytesWritten);
    if (res != FR_OK || bytesWritten != strlen(buf))
    {
        printf("Write File Failed: %d\n", res);
    }
    else
    {
        printf("RTC Time Saved to File: %s", buf);
    }

    // �ر��ļ����ļ�ϵͳ
    f_close(&file);
    f_mount(0, "", 0);
}

// ���ļ����� RTC ʱ��
void RTC_LoadTimeFromFile(void)
{
    FATFS fs;
    FIL file;
    FRESULT res;
    char buf[50] = {0};
    UINT bytesRead;
    uint8_t year, month, date, hour, min, sec, weekday;
    // �����ļ�ϵͳ
    res = f_mount(&fs, "", 1);
    if (res != FR_OK)
    {
        printf("Mount FS Failed: %d\n", res);
        return;
    }
    // ���ļ����Զ�ȡģʽ��
    res = f_open(&file, RTC_TIME_FILE, FA_READ);
    if (res != FR_OK)
    {
        if (res == FR_NO_FILE) {
            printf("RTC time file does not exist, will use default time\n");
        } else {
            printf("Open File Failed: %d\n", res);
        }
        f_mount(0, "", 0); // ж���ļ�ϵͳ
        return;
    }
    // ��ȡ�ļ�����
    res = f_read(&file, buf, sizeof(buf) - 1, &bytesRead);
    if (res != FR_OK || bytesRead == 0)
    {
        printf("Read File Failed: %d\n", res);
        f_close(&file);
        f_mount(0, "", 0);
        return;
    }
    // ����ʱ������
    if (sscanf(buf, "20%hhu-%hhu-%hhu %hhu:%hhu:%hhu %hhu",
               &year, &month, &date, &hour, &min, &sec, &weekday) == 7)
    {
        // ���� RTC ʱ�������
        RTC_Set_Date(year, month, date, weekday);
        RTC_Set_Time(hour, min, sec, RTC_HOURFORMAT12_AM);
        printf("RTC Time Loaded from File: %s", buf);
    }
    else
    {
        printf("Parse File Content Failed: %s\n", buf);
    }
    // �ر��ļ����ļ�ϵͳ
    f_close(&file);
    f_mount(0, "", 0);
}


// �Ľ���RTC��Ԫ����
void rtc_unit_test(void)
{
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;
    uint8_t tbuf[200];
    uint32_t saveCounter = 0;  // ʹ�ü��������HAL_GetTick()
    uint8_t timeLoaded = 0;    // ����Ƿ�ɹ�����ʱ��

    // ��ʼ�� RTC
    RTC_Init();
		RTC_LoadTimeFromFile();
    // ���� WAKE UP �ж�
    RTC_Set_WakeUp(RTC_WAKEUPCLOCK_CK_SPRE_16BITS, 0);

    printf("Starting main loop...\n");

    // ��ѭ��
    while (1)
    {
        HAL_RTC_GetTime(&RTC_Handler, &RTC_TimeStruct, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN);

        sprintf((char *)tbuf, "Date: 20%02d-%02d-%02d  Time: %02d:%02d:%02d  Week: %d",
                RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date,
                RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds,
                RTC_DateStruct.WeekDay);

        printf("%s\n", tbuf);

        // ʹ�ü���������HAL_GetTick()���ж�ʱ����
        // ÿ120��ѭ������һ�Σ�Լ60�룬��ΪHAL_Delay(500)��
        saveCounter++;
        if (saveCounter >= 10)  
        {
            printf("Saving RTC Time to File... (Counter: %d)\n", saveCounter);
            RTC_SaveTimeToFile();
            saveCounter = 0;  // ���ü�����
        }

        HAL_Delay(500);
    }
}
