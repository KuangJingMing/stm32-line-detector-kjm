/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_scrSetting(lv_ui *ui)
{
    //Write codes scrSetting
    ui->scrSetting = lv_obj_create(NULL);
    lv_obj_set_size(ui->scrSetting, 800, 480);
    lv_obj_set_scrollbar_mode(ui->scrSetting, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting, lv_color_hex(0xF3F8FE), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_contBG
    ui->scrSetting_contBG = lv_obj_create(ui->scrSetting);
    lv_obj_set_pos(ui->scrSetting_contBG, 0, 0);
    lv_obj_set_size(ui->scrSetting_contBG, 800, 105);
    lv_obj_set_scrollbar_mode(ui->scrSetting_contBG, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting_contBG, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_contBG, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_contBG, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_contBG, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_labelTitle
    ui->scrSetting_labelTitle = lv_label_create(ui->scrSetting);
    lv_label_set_text(ui->scrSetting_labelTitle, "设置模式");
    lv_label_set_long_mode(ui->scrSetting_labelTitle, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrSetting_labelTitle, 225, 40);
    lv_obj_set_size(ui->scrSetting_labelTitle, 350, 56);

    //Write style for scrSetting_labelTitle, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_labelTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_labelTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_labelTitle, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_labelTitle, &lv_font_SourceHanSerifSC_Regular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_labelTitle, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_labelTitle, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrSetting_labelTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_labelTitle, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_labelTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_labelTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_labelTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_labelTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_labelTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_labelTitle, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_btnBack
    ui->scrSetting_btnBack = lv_btn_create(ui->scrSetting);
    ui->scrSetting_btnBack_label = lv_label_create(ui->scrSetting_btnBack);
    lv_label_set_text(ui->scrSetting_btnBack_label, "<");
    lv_label_set_long_mode(ui->scrSetting_btnBack_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scrSetting_btnBack_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scrSetting_btnBack, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scrSetting_btnBack_label, LV_PCT(100));
    lv_obj_set_pos(ui->scrSetting_btnBack, 41, 30);
    lv_obj_set_size(ui->scrSetting_btnBack, 58, 56);

    //Write style for scrSetting_btnBack, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_btnBack, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_btnBack, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_btnBack, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_btnBack, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_btnBack, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_btnBack, &lv_font_montserratMedium_41, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_btnBack, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_btnBack, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_cont_setting
    ui->scrSetting_cont_setting = lv_obj_create(ui->scrSetting);
    lv_obj_set_pos(ui->scrSetting_cont_setting, 44, 82);
    lv_obj_set_size(ui->scrSetting_cont_setting, 712, 347);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_setting, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting_cont_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_setting, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_setting, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_setting, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_setting, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_year
    ui->scrSetting_ta_year = lv_textarea_create(ui->scrSetting_cont_setting);
    lv_textarea_set_text(ui->scrSetting_ta_year, "");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_year, "年");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_year, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_year, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_year, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_year, "0123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_year, 4);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_year, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_year, 115, 42);
    lv_obj_set_size(ui->scrSetting_ta_year, 200, 60);

    //Write style for scrSetting_ta_year, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_year, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_year, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_year, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_year, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_year, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_year, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_year, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_year, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_year, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_year, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_year, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_year, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_year, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_year, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_year, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_year, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_year, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_year, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_year, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_year, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_year, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_month
    ui->scrSetting_ta_month = lv_textarea_create(ui->scrSetting_cont_setting);
    lv_textarea_set_text(ui->scrSetting_ta_month, "");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_month, "月");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_month, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_month, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_month, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_month, "123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_month, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_month, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_month, 376, 42);
    lv_obj_set_size(ui->scrSetting_ta_month, 200, 60);

    //Write style for scrSetting_ta_month, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_month, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_month, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_month, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_month, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_month, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_month, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_month, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_month, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_month, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_month, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_month, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_month, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_month, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_month, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_month, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_month, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_month, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_month, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_month, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_month, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_month, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_day
    ui->scrSetting_ta_day = lv_textarea_create(ui->scrSetting_cont_setting);
    lv_textarea_set_text(ui->scrSetting_ta_day, "");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_day, "日");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_day, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_day, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_day, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_day, "123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_day, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_day, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_day, 115, 123);
    lv_obj_set_size(ui->scrSetting_ta_day, 200, 60);

    //Write style for scrSetting_ta_day, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_day, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_day, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_day, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_day, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_day, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_day, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_day, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_day, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_day, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_day, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_day, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_day, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_day, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_day, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_day, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_day, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_day, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_day, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_day, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_day, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_day, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_hour
    ui->scrSetting_ta_hour = lv_textarea_create(ui->scrSetting_cont_setting);
    lv_textarea_set_text(ui->scrSetting_ta_hour, "");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_hour, "时");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_hour, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_hour, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_hour, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_hour, "123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_hour, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_hour, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_hour, 376, 123);
    lv_obj_set_size(ui->scrSetting_ta_hour, 200, 60);

    //Write style for scrSetting_ta_hour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_hour, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_hour, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_hour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_hour, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_hour, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_hour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_hour, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_hour, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_hour, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_hour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_hour, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_hour, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_hour, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_hour, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_hour, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_hour, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_hour, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_hour, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_hour, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_hour, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_hour, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_minute
    ui->scrSetting_ta_minute = lv_textarea_create(ui->scrSetting_cont_setting);
    lv_textarea_set_text(ui->scrSetting_ta_minute, "");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_minute, "分");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_minute, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_minute, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_minute, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_minute, "123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_minute, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_minute, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_minute, 115, 204);
    lv_obj_set_size(ui->scrSetting_ta_minute, 200, 60);

    //Write style for scrSetting_ta_minute, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_minute, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_minute, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_minute, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_minute, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_minute, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_minute, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_minute, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_minute, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_minute, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_minute, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_minute, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_minute, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_minute, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_minute, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_minute, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_minute, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_minute, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_minute, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_minute, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_minute, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_minute, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_minute, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_second
    ui->scrSetting_ta_second = lv_textarea_create(ui->scrSetting_cont_setting);
    lv_textarea_set_text(ui->scrSetting_ta_second, "");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_second, "秒");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_second, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_second, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_second, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_second, "123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_second, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_second, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_second, 376, 204);
    lv_obj_set_size(ui->scrSetting_ta_second, 200, 60);

    //Write style for scrSetting_ta_second, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_second, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_second, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_second, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_second, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_second, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_second, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_second, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_second, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_second, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_second, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_second, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_second, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_second, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_second, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_second, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_second, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_second, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_second, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_second, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_second, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_second, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_btn_1
    ui->scrSetting_btn_1 = lv_btn_create(ui->scrSetting_cont_setting);
    ui->scrSetting_btn_1_label = lv_label_create(ui->scrSetting_btn_1);
    lv_label_set_text(ui->scrSetting_btn_1_label, "设置");
    lv_label_set_long_mode(ui->scrSetting_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scrSetting_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scrSetting_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scrSetting_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->scrSetting_btn_1, 119, 280);
    lv_obj_set_size(ui->scrSetting_btn_1, 200, 50);

    //Write style for scrSetting_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_btn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_btn_1, lv_color_hex(0x5482a9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_btn_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_btn_1, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_btn_1, lv_color_hex(0x12548b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_btn_1, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_btn_2
    ui->scrSetting_btn_2 = lv_btn_create(ui->scrSetting_cont_setting);
    ui->scrSetting_btn_2_label = lv_label_create(ui->scrSetting_btn_2);
    lv_label_set_text(ui->scrSetting_btn_2_label, "返回");
    lv_label_set_long_mode(ui->scrSetting_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scrSetting_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scrSetting_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scrSetting_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->scrSetting_btn_2, 363, 284);
    lv_obj_set_size(ui->scrSetting_btn_2, 200, 50);

    //Write style for scrSetting_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_btn_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_btn_2, lv_color_hex(0x5482a9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_btn_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_btn_2, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_btn_2, lv_color_hex(0x12548b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_btn_2, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of scrSetting.


    //Update current screen layout.
    lv_obj_update_layout(ui->scrSetting);

    //Init events for screen.
    events_init_scrSetting(ui);
}
