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
#include "custom.h"

static void scrHome_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        ui_animation(guider_ui.scrHome_contBG, 150, 0, lv_obj_get_width(guider_ui.scrHome_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrHome_contBG, 150, 0, lv_obj_get_height(guider_ui.scrHome_contBG), 150, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        custom_init(&guider_ui);
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
        ui_load_scr_animation(&guider_ui, &guider_ui.scrSetting, guider_ui.scrSetting_del, &guider_ui.scrHome_del, setup_scr_scrSetting, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
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
        ui_load_scr_animation(&guider_ui, &guider_ui.screenLog, guider_ui.screenLog_del, &guider_ui.scrHome_del, setup_scr_screenLog, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
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
        ui_load_scr_animation(&guider_ui, &guider_ui.scrLoader, guider_ui.scrLoader_del, &guider_ui.scrHome_del, setup_scr_scrLoader, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
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
        ui_load_scr_animation(&guider_ui, &guider_ui.scrLoader, guider_ui.scrLoader_del, &guider_ui.scrHome_del, setup_scr_scrLoader, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        set_screen_mode(DETECTION_MODE);
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
        } else if (get_current_mode() == DETECTION_MODE) {
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
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.scrComplete_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
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
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.scrComplete_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
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
        if (get_current_mode() == STUDY_MODE)
        {
            lv_label_set_text(guider_ui.scrLoader_labelPrompt, "正在学习中请稍后");
        } else if (get_current_mode() == DETECTION_MODE) {
            lv_label_set_text(guider_ui.scrLoader_labelPrompt, "正在检测中请稍后");
        }
        lv_anim_t loader_arc;
        lv_anim_init(&loader_arc);
        lv_anim_set_exec_cb(&loader_arc, (lv_anim_exec_xcb_t)lv_arc_set_end_angle);
        lv_anim_set_values(&loader_arc, 0, 360);
        lv_anim_set_time(&loader_arc, 1000);
        lv_anim_set_delay(&loader_arc, 50);
        lv_anim_set_var(&loader_arc, guider_ui.scrLoader_arcLoader);
        lv_anim_start(&loader_arc);

        lv_anim_t loader_tp;
        lv_anim_init(&loader_tp);
        lv_anim_set_exec_cb(&loader_tp, (lv_anim_exec_xcb_t)lv_textprogress_set_value);
        lv_anim_set_values(&loader_tp, 0, 100);
        lv_anim_set_time(&loader_tp, 1000);
        lv_anim_set_delay(&loader_tp, 50);
        lv_anim_set_var(&loader_tp, guider_ui.scrLoader_tpLoader);
        lv_anim_start(&loader_tp);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrComplete, guider_ui.scrComplete_del, &guider_ui.scrLoader_del, setup_scr_scrComplete, LV_SCR_LOAD_ANIM_NONE, 200, 1500, false, true);
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

static void screenLog_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        init_custom_log_list(&guider_ui);
        ui_animation(guider_ui.screenLog_contBG, 150, 0, lv_obj_get_width(guider_ui.screenLog_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.screenLog_contBG, 150, 0, lv_obj_get_height(guider_ui.screenLog_contBG), 150, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

static void screenLog_btnBack_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_width(guider_ui.screenLog_contBG, 800);
        lv_obj_set_height(guider_ui.screenLog_contBG, 105);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.screenLog_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screenLog (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screenLog, screenLog_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screenLog_btnBack, screenLog_btnBack_event_handler, LV_EVENT_ALL, ui);
}

static void scrSetting_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        custom_scr_setting_init(&guider_ui);
        ui_animation(guider_ui.scrSetting_contBG, 150, 0, lv_obj_get_width(guider_ui.scrSetting_contBG), 800, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_width, NULL, NULL, NULL);
        ui_animation(guider_ui.scrSetting_contBG, 150, 0, lv_obj_get_height(guider_ui.scrSetting_contBG), 150, &lv_anim_path_ease_out, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_height, NULL, NULL, NULL);
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
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.scrSetting_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
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
        lv_label_set_text(guider_ui.scrSetting_labelTitle, "设置成功");
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
        lv_obj_set_width(guider_ui.scrSetting_contBG, 800);
        lv_obj_set_height(guider_ui.scrSetting_contBG, 105);
        ui_load_scr_animation(&guider_ui, &guider_ui.scrHome, guider_ui.scrHome_del, &guider_ui.scrSetting_del, setup_scr_scrHome, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
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
    lv_obj_add_event_cb(ui->scrSetting_btn_1, scrSetting_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->scrSetting_btn_2, scrSetting_btn_2_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
