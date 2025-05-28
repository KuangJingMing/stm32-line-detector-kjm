/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "custom.h"

static void scrHome_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.scrHome_contBG, 150, 0, lv_obj_get_width(guider_ui.scrHome_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrHome_contBG, 150, 0, lv_obj_get_height(guider_ui.scrHome_contBG), 150, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        reload_ink_bar_animations(&guider_ui);
        break;
    }
    default:
        break;
    }
}

static void scrHome_contSetup_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_animation(guider_ui.scrHome_contBG, 200, 0, lv_obj_get_width(guider_ui.scrHome_contBG), 800, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrHome_contBG, 200, 0, lv_obj_get_height(guider_ui.scrHome_contBG), 105, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrSetting, guider_ui.scrSetting_del, &guider_ui.scrHome_del, setup_scr_scrSetting, LV_SCR_LOAD_ANIM_FADE_ON, 200, 50, false, false);
        break;
    }
    default:
        break;
    }
}

static void scrHome_contPrint_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_animation(guider_ui.scrHome_contBG, 200, 0, lv_obj_get_width(guider_ui.scrHome_contBG), 800, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrHome_contBG, 200, 0, lv_obj_get_height(guider_ui.scrHome_contBG), 105, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrLog, guider_ui.scrLog_del, &guider_ui.scrHome_del, setup_scr_scrLog, LV_SCR_LOAD_ANIM_FADE_ON, 200, 50, false, false);
        break;
    }
    default:
        break;
    }
}

static void scrHome_contCopy_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_animation(guider_ui.scrHome_contBG, 200, 0, lv_obj_get_width(guider_ui.scrHome_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrHome_contBG, 200, 0, lv_obj_get_height(guider_ui.scrHome_contBG), 105, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrLoader, guider_ui.scrLoader_del, &guider_ui.scrHome_del, setup_scr_scrLoader, LV_SCR_LOAD_ANIM_FADE_ON, 200, 50, false, false);
        set_screen_mode(STUDY_MODE);
        break;
    }
    default:
        break;
    }
}

static void scrHome_contScan_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_animation(guider_ui.scrHome_contBG, 200, 0, lv_obj_get_width(guider_ui.scrHome_contBG), 800, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrHome_contBG, 200, 0, lv_obj_get_height(guider_ui.scrHome_contBG), 105, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrDetect, guider_ui.scrDetect_del, &guider_ui.scrHome_del, setup_scr_scrDetect, LV_SCR_LOAD_ANIM_FADE_ON, 200, 50, false, false);
        break;
    }
    default:
        break;
    }
}

void events_init_scrHome (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scrHome, scrHome_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrHome_contSetup, scrHome_contSetup_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrHome_contPrint, scrHome_contPrint_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrHome_contCopy, scrHome_contCopy_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrHome_contScan, scrHome_contScan_event_handler, LV_EVENT_ALL, ui);
}

static void scrComplete_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        if (get_current_mode() == STUDY_MODE) {
            lv_label_set_text(guider_ui.scrComplete_labelTitle, "金样学习完成");
            lv_label_set_text(guider_ui.scrComplete_label_1, "0错误0警告");
        } else if (get_current_mode() == DETECTION_MODE_42  ||
                   get_current_mode() == DETECTION_MODE_47  ||
                   get_current_mode() == DETECTION_MODE_100 ||
                   get_current_mode() == DETECTION_MODE_NORMAL) {
            lv_label_set_text(guider_ui.scrComplete_labelTitle, "检测完成");
            lv_label_set_text(guider_ui.scrComplete_label_1, "0错误0警告");
        }
        ui_animation(guider_ui.scrComplete_contBG, 150, 0, lv_obj_get_width(guider_ui.scrComplete_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrComplete_contBG, 159, 0, lv_obj_get_height(guider_ui.scrComplete_contBG), 150, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void scrComplete_btnNext_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.scrComplete_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, false);
        ui_animation(guider_ui.scrComplete_contBG, 200, 0, lv_obj_get_width(guider_ui.scrComplete_contBG), 800, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrComplete_contBG, 200, 0, lv_obj_get_height(guider_ui.scrComplete_contBG), 105, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void scrComplete_btnBack_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.scrComplete_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, false);
        ui_animation(guider_ui.scrComplete_contBG, 200, 0, lv_obj_get_width(guider_ui.scrComplete_contBG), 800, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrComplete_contBG, 200, 0, lv_obj_get_height(guider_ui.scrComplete_contBG), 105, &lv_anim_path_ease_in, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

void events_init_scrComplete (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scrComplete, scrComplete_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrComplete_btnNext, scrComplete_btnNext_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrComplete_btnBack, scrComplete_btnBack_event_handler, LV_EVENT_ALL, ui);
}

static void scrLoader_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        if (get_current_mode() == STUDY_MODE) {
            lv_label_set_text(guider_ui.scrLoader_labelPrompt, "正在学习中请稍后");
        } else {
            int mode = get_current_mode();
            const char* line = (mode == DETECTION_MODE_42) ? "42线" :
                               (mode == DETECTION_MODE_47) ? "47线" :
                               (mode == DETECTION_MODE_100) ? "100线" :
                               (mode == DETECTION_MODE_NORMAL) ? "样本数据" : "";

            static char temp_str[50];
            snprintf(temp_str, sizeof(temp_str), "正在检测%s中请稍后", line);
            lv_label_set_text(guider_ui.scrLoader_labelPrompt, temp_str);
        }

#define LOADER_ANIM_TIME    1000
#define LOADER_ANIM_DELAY   50

        // 弧形加载器动画
        lv_anim_t loader_arc;
        lv_anim_init(&loader_arc);
        lv_anim_set_exec_cb(&loader_arc, (lv_anim_exec_xcb_t)lv_arc_set_end_angle);
        lv_anim_set_values(&loader_arc, 0, 360);
        lv_anim_set_time(&loader_arc, LOADER_ANIM_TIME);
        lv_anim_set_delay(&loader_arc, LOADER_ANIM_DELAY);
        lv_anim_set_var(&loader_arc, guider_ui.scrLoader_arcLoader);
        lv_anim_start(&loader_arc);

        // 文本进度条动画
        lv_anim_t loader_tp;
        lv_anim_init(&loader_tp);
        lv_anim_set_exec_cb(&loader_tp, (lv_anim_exec_xcb_t)lv_textprogress_set_value);
        lv_anim_set_values(&loader_tp, 0, 100);
        lv_anim_set_time(&loader_tp, LOADER_ANIM_TIME);
        lv_anim_set_delay(&loader_tp, LOADER_ANIM_DELAY);
        lv_anim_set_var(&loader_tp, guider_ui.scrLoader_tpLoader);
        lv_anim_start(&loader_tp);

        ui_load_scr_animation(&guider_ui, &guider_ui.scrComplete, guider_ui.scrComplete_del, &guider_ui.scrLoader_del, setup_scr_scrComplete, LV_SCR_LOAD_ANIM_NONE, 200, 1500, false, false);
        break;
    }
    default:
        break;
    }
}

void events_init_scrLoader (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scrLoader, scrLoader_event_handler, LV_EVENT_ALL, ui);
}

static void scrLog_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        init_custom_log_list(&guider_ui);
        ui_animation(guider_ui.scrLog_contBG, 150, 0, lv_obj_get_width(guider_ui.scrLog_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrLog_contBG, 150, 0, lv_obj_get_height(guider_ui.scrLog_contBG), 150, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void scrLog_btnBack_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_width(guider_ui.scrLog_contBG, 800);
        lv_obj_set_height(guider_ui.scrLog_contBG, 105);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.scrLog_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, false);
        break;
    }
    default:
        break;
    }
}

void events_init_scrLog (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scrLog, scrLog_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrLog_btnBack, scrLog_btnBack_event_handler, LV_EVENT_ALL, ui);
}

static void scrSetting_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.scrSetting_contBG, 150, 0, lv_obj_get_width(guider_ui.scrSetting_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrSetting_contBG, 150, 0, lv_obj_get_height(guider_ui.scrSetting_contBG), 150, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        lv_label_set_text(guider_ui.scrSetting_labelTitle, "设置模式");
        lv_obj_clear_flag(guider_ui.scrSetting_list_1, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void scrSetting_btnBack_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_width(guider_ui.scrSetting_contBG, 800);
        lv_obj_set_height(guider_ui.scrSetting_contBG, 105);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.scrSetting_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, false);
        break;
    }
    default:
        break;
    }
}

static void scrSetting_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.scrSetting_cont_log, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.scrSetting_list_1, LV_OBJ_FLAG_HIDDEN);

        break;
    }
    default:
        break;
    }
}

static void scrSetting_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_label_set_text(guider_ui.scrSetting_labelTitle, "设置时间成功");

        break;
    }
    default:
        break;
    }
}

static void scrSetting_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.scrSetting_cont_time_setting, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.scrSetting_list_1, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(guider_ui.scrSetting_labelTitle, "设置模式");

        break;
    }
    default:
        break;
    }
}

static void scrSetting_list_1_item0_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_clear_flag(guider_ui.scrSetting_cont_time_setting, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scrSetting_list_1, LV_OBJ_FLAG_HIDDEN);

        break;
    }
    default:
        break;
    }
}

static void scrSetting_list_1_item1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_clear_flag(guider_ui.scrSetting_cont_log, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.scrSetting_list_1, LV_OBJ_FLAG_HIDDEN);

        break;
    }
    default:
        break;
    }
}

static void scrSetting_list_1_item3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

void events_init_scrSetting (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scrSetting, scrSetting_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrSetting_btnBack, scrSetting_btnBack_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrSetting_btn_3, scrSetting_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrSetting_btn_1, scrSetting_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrSetting_btn_2, scrSetting_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrSetting_list_1_item0, scrSetting_list_1_item0_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrSetting_list_1_item1, scrSetting_list_1_item1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrSetting_list_1_item3, scrSetting_list_1_item3_event_handler, LV_EVENT_ALL, ui);
}

static void scrDetect_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.scrDetect_contBG, 150, 0, lv_obj_get_width(guider_ui.scrDetect_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrDetect_contBG, 150, 0, lv_obj_get_height(guider_ui.scrDetect_contBG), 150, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void scrDetect_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.scrDetect_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, false);
        ui_animation(guider_ui.scrDetect_contBG, 150, 0, lv_obj_get_width(guider_ui.scrDetect_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrDetect_contBG, 150, 0, lv_obj_get_height(guider_ui.scrDetect_contBG), 105, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void scrDetect_cont_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        set_screen_mode(DETECTION_MODE_NORMAL);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrLoader, guider_ui.scrLoader_del, &guider_ui.scrDetect_del, setup_scr_scrLoader, LV_SCR_LOAD_ANIM_NONE, 200, 50, false, false);
        ui_animation(guider_ui.scrDetect_contBG, 150, 0, lv_obj_get_width(guider_ui.scrDetect_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrDetect_contBG, 150, 0, lv_obj_get_height(guider_ui.scrDetect_contBG), 105, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void scrDetect_cont_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        set_screen_mode(DETECTION_MODE_42);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrLoader, guider_ui.scrLoader_del, &guider_ui.scrDetect_del, setup_scr_scrLoader, LV_SCR_LOAD_ANIM_NONE, 200, 50, false, false);
        lv_obj_set_width(guider_ui.scrDetect_contBG, 800);
        lv_obj_set_height(guider_ui.scrDetect_contBG, 105);
        break;
    }
    default:
        break;
    }
}

static void scrDetect_cont_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        set_screen_mode(DETECTION_MODE_47);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrLoader, guider_ui.scrLoader_del, &guider_ui.scrDetect_del, setup_scr_scrLoader, LV_SCR_LOAD_ANIM_NONE, 200, 50, false, false);
        lv_obj_set_width(guider_ui.scrDetect_contBG, 800);
        lv_obj_set_height(guider_ui.scrDetect_contBG, 105);
        break;
    }
    default:
        break;
    }
}

static void scrDetect_cont_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        set_screen_mode(DETECTION_MODE_100);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrLoader, guider_ui.scrLoader_del, &guider_ui.scrDetect_del, setup_scr_scrLoader, LV_SCR_LOAD_ANIM_NONE, 200, 50, false, false);
        lv_obj_set_width(guider_ui.scrDetect_contBG, 800);
        lv_obj_set_height(guider_ui.scrDetect_contBG, 105);
        break;
    }
    default:
        break;
    }
}

void events_init_scrDetect (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->scrDetect, scrDetect_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrDetect_btn_1, scrDetect_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrDetect_cont_5, scrDetect_cont_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrDetect_cont_2, scrDetect_cont_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrDetect_cont_3, scrDetect_cont_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrDetect_cont_4, scrDetect_cont_4_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
