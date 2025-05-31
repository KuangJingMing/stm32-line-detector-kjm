#include "../App/gui_backend.h"
#include "custom.h"
#include "gui_guider.h"
#include "lvgl.h"
#include "main.h"

extern lv_ui guider_ui;
char date_time_buffer[32];  

void gui_update_time_label(void)
{
    if (guider_ui.scrHome_labelDate == NULL)
        return;
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;
    HAL_RTC_GetTime(&RTC_Handler, &RTC_TimeStruct, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN);
		snprintf(date_time_buffer, sizeof(date_time_buffer),
         "20%02d-%02d-%02d %02d:%02d:%02d",
         RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date,
         RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);

		lv_label_set_text(guider_ui.scrHome_labelDate, date_time_buffer);
}

void gui_set_time(void)
{
    RTC_TimeTypeDef RTC_TimeStructure = {0};
    RTC_DateTypeDef RTC_DateStructure = {0};
    int year = atoi(lv_textarea_get_text(guider_ui.scrSetting_ta_2));
    int month = atoi(lv_textarea_get_text(guider_ui.scrSetting_ta_3));
    int date = atoi(lv_textarea_get_text(guider_ui.scrSetting_ta_4));
    int hour = atoi(lv_textarea_get_text(guider_ui.scrSetting_ta_5));
    int minute = atoi(lv_textarea_get_text(guider_ui.scrSetting_ta_6));
    int second = atoi(lv_textarea_get_text(guider_ui.scrSetting_ta_7));
    if (year > 2000)
        year -= 2000;
    if (month < 1 || month > 12)
        month = 1;
    if (date < 1 || date > 31)
        date = 1;
    if (hour < 0 || hour > 23)
        hour = 0;
    if (minute < 0 || minute > 59)
        minute = 0;
    if (second < 0 || second > 59)
        second = 0;
    // 填充日期
    RTC_DateStructure.Year = year;   // 0~99
    RTC_DateStructure.Month = month; // 1~12
    RTC_DateStructure.Date = date;   // 1~31
    // 填充时间
    RTC_TimeStructure.Hours = hour;                     // 0~23
    RTC_TimeStructure.Minutes = minute;                 // 0~59
    RTC_TimeStructure.Seconds = second;                 // 0~59
    RTC_TimeStructure.TimeFormat = RTC_HOURFORMAT12_AM; // 24小时制
    RTC_TimeStructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    RTC_TimeStructure.StoreOperation = RTC_STOREOPERATION_RESET;
    // 先设置日期
    HAL_RTC_SetDate(&RTC_Handler, &RTC_DateStructure, RTC_FORMAT_BIN);
    // 再设置时间
    HAL_RTC_SetTime(&RTC_Handler, &RTC_TimeStructure, RTC_FORMAT_BIN);
}

void gui_backend_task_handler(void)
{
    static uint32_t last_tick;
    static uint32_t timeout = 1000;
    if ((HAL_GetTick() - last_tick) > timeout)
    {
        gui_update_time_label();
        last_tick = HAL_GetTick();
    }
}