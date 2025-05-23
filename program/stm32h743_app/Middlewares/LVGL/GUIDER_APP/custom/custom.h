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

typedef enum {
    STUDY_MODE,
    DETECTION_MODE,
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

void init_custom_log_list(lv_ui *ui);
void custom_scr_setting_init(lv_ui *ui);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
