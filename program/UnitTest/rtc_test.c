#include "main.h"
#include <stdio.h>
#include <string.h>
#include "ff.h"         /* FatFs 头文件 */
#include "diskio.h"     /* 磁盘 I/O 接口 */

// 文件路径
#define RTC_TIME_FILE "rtc_time.txt"

// 保存 RTC 时间到文件
void RTC_SaveTimeToFile(void)
{
    FATFS fs;
    FIL file;
    FRESULT res;
    char buf[50];
    UINT bytesWritten;
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;

    // 获取当前时间和日期
    HAL_RTC_GetTime(&RTC_Handler, &RTC_TimeStruct, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN);

    // 挂载文件系统
    res = f_mount(&fs, "", 1);
    if (res != FR_OK)
    {
        printf("Mount FS Failed: %d\n", res);
        return;
    }

    // 打开文件（以写入模式）
    res = f_open(&file, RTC_TIME_FILE, FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK)
    {
        printf("Open File Failed: %d\n", res);
        f_mount(0, "", 0); // 卸载文件系统
        return;
    }

    // 格式化时间数据为字符串
    sprintf(buf, "20%02d-%02d-%02d %02d:%02d:%02d %d\n",
            RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date,
            RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds,
            RTC_DateStruct.WeekDay);

    // 写入文件
    res = f_write(&file, buf, strlen(buf), &bytesWritten);
    if (res != FR_OK || bytesWritten != strlen(buf))
    {
        printf("Write File Failed: %d\n", res);
    }
    else
    {
        printf("RTC Time Saved to File: %s", buf);
    }

    // 关闭文件和文件系统
    f_close(&file);
    f_mount(0, "", 0);
}

// 从文件加载 RTC 时间
void RTC_LoadTimeFromFile(void)
{
    FATFS fs;
    FIL file;
    FRESULT res;
    char buf[50] = {0};
    UINT bytesRead;
    uint8_t year, month, date, hour, min, sec, weekday;
    // 挂载文件系统
    res = f_mount(&fs, "", 1);
    if (res != FR_OK)
    {
        printf("Mount FS Failed: %d\n", res);
        return;
    }
    // 打开文件（以读取模式）
    res = f_open(&file, RTC_TIME_FILE, FA_READ);
    if (res != FR_OK)
    {
        if (res == FR_NO_FILE) {
            printf("RTC time file does not exist, will use default time\n");
        } else {
            printf("Open File Failed: %d\n", res);
        }
        f_mount(0, "", 0); // 卸载文件系统
        return;
    }
    // 读取文件内容
    res = f_read(&file, buf, sizeof(buf) - 1, &bytesRead);
    if (res != FR_OK || bytesRead == 0)
    {
        printf("Read File Failed: %d\n", res);
        f_close(&file);
        f_mount(0, "", 0);
        return;
    }
    // 解析时间数据
    if (sscanf(buf, "20%hhu-%hhu-%hhu %hhu:%hhu:%hhu %hhu",
               &year, &month, &date, &hour, &min, &sec, &weekday) == 7)
    {
        // 设置 RTC 时间和日期
        RTC_Set_Date(year, month, date, weekday);
        RTC_Set_Time(hour, min, sec, RTC_HOURFORMAT12_AM);
        printf("RTC Time Loaded from File: %s", buf);
    }
    else
    {
        printf("Parse File Content Failed: %s\n", buf);
    }
    // 关闭文件和文件系统
    f_close(&file);
    f_mount(0, "", 0);
}


// 改进的RTC单元测试
void rtc_unit_test(void)
{
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;
    uint8_t tbuf[200];
    uint32_t saveCounter = 0;  // 使用计数器替代HAL_GetTick()
    uint8_t timeLoaded = 0;    // 标记是否成功加载时间

    // 初始化 RTC
    RTC_Init();
		RTC_LoadTimeFromFile();
    // 配置 WAKE UP 中断
    RTC_Set_WakeUp(RTC_WAKEUPCLOCK_CK_SPRE_16BITS, 0);

    printf("Starting main loop...\n");

    // 主循环
    while (1)
    {
        HAL_RTC_GetTime(&RTC_Handler, &RTC_TimeStruct, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN);

        sprintf((char *)tbuf, "Date: 20%02d-%02d-%02d  Time: %02d:%02d:%02d  Week: %d",
                RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date,
                RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds,
                RTC_DateStruct.WeekDay);

        printf("%s\n", tbuf);

        // 使用计数器代替HAL_GetTick()进行定时保存
        // 每120次循环保存一次（约60秒，因为HAL_Delay(500)）
        saveCounter++;
        if (saveCounter >= 10)  
        {
            printf("Saving RTC Time to File... (Counter: %d)\n", saveCounter);
            RTC_SaveTimeToFile();
            saveCounter = 0;  // 重置计数器
        }

        HAL_Delay(500);
    }
}
