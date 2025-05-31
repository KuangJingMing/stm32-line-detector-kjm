/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32H743xx
    #include "main.h"
#endif 

/**********************
TYPEDEFS
**********************/
typedef struct {
    char text[100];           // 日志文本
    lv_obj_t *item_obj;      // 对应的UI对象
    int index;               // 日志索引
} log_item_t;

typedef enum {
    STUDY_MODE,
    DETECTION_MODE_42,
    DETECTION_MODE_47,
    DETECTION_MODE_100,
    DETECTION_MODE_NORMAL,
    LOG_MODE,
    SETTING_MODE,
} SCREEN_MODE;

#include "gui_guider.h"

void custom_init(lv_ui *ui);

/**********************
 *  自定义函数
 **********************/
void set_screen_mode(SCREEN_MODE mode);
SCREEN_MODE get_current_mode(void);
void add_log_item_without_save(lv_ui *ui, const char *text);
void add_log_item_without_save_with_index(lv_ui *ui, const char *text, int index);

void init_custom_log_list(lv_ui *ui);

void reload_ink_bar_animations(lv_ui *ui);

void custom_scr_setting_init(lv_ui *ui);
void custom_scr_detect_init(lv_ui *ui);

void disable_keyboard(lv_ui *ui);
void enable_keyboard(lv_ui *ui);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
