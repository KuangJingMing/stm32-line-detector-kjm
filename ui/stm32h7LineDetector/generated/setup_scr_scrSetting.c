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

    //Write codes scrSetting_cont_time_setting
    ui->scrSetting_cont_time_setting = lv_obj_create(ui->scrSetting);
    lv_obj_set_pos(ui->scrSetting_cont_time_setting, 44, 82);
    lv_obj_set_size(ui->scrSetting_cont_time_setting, 712, 347);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_time_setting, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->scrSetting_cont_time_setting, LV_OBJ_FLAG_HIDDEN);

    //Write style for scrSetting_cont_time_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_time_setting, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_time_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_time_setting, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_time_setting, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_time_setting, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_time_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_time_setting, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_time_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_time_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_time_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_time_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_time_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_time_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_cont_year
    ui->scrSetting_cont_year = lv_obj_create(ui->scrSetting_cont_time_setting);
    lv_obj_set_pos(ui->scrSetting_cont_year, 107, 20);
    lv_obj_set_size(ui->scrSetting_cont_year, 187, 63);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_year, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting_cont_year, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_year, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_year, 90, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_year, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_year, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_year, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_year, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_year, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_year, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_label_8
    ui->scrSetting_label_8 = lv_label_create(ui->scrSetting_cont_year);
    lv_label_set_text(ui->scrSetting_label_8, "年：");
    lv_label_set_long_mode(ui->scrSetting_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrSetting_label_8, 19, 16);
    lv_obj_set_size(ui->scrSetting_label_8, 40, 32);

    //Write style for scrSetting_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_label_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_label_8, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_2
    ui->scrSetting_ta_2 = lv_textarea_create(ui->scrSetting_cont_year);
    lv_textarea_set_text(ui->scrSetting_ta_2, "2025");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_2, "年");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_2, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_2, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_2, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_2, "0123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_2, 4);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_2, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_2, 67, 7);
    lv_obj_set_size(ui->scrSetting_ta_2, 91, 40);
    lv_obj_add_flag(ui->scrSetting_ta_2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    //Write style for scrSetting_ta_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_2, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_2, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_2, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_2, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_2, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_2, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_2, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_cont_month
    ui->scrSetting_cont_month = lv_obj_create(ui->scrSetting_cont_time_setting);
    lv_obj_set_pos(ui->scrSetting_cont_month, 361, 16);
    lv_obj_set_size(ui->scrSetting_cont_month, 187, 63);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_month, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting_cont_month, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_month, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_month, 90, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_month, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_month, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_month, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_month, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_month, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_month, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_label_9
    ui->scrSetting_label_9 = lv_label_create(ui->scrSetting_cont_month);
    lv_label_set_text(ui->scrSetting_label_9, "月：");
    lv_label_set_long_mode(ui->scrSetting_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrSetting_label_9, 19, 16);
    lv_obj_set_size(ui->scrSetting_label_9, 40, 32);

    //Write style for scrSetting_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_label_9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_label_9, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_3
    ui->scrSetting_ta_3 = lv_textarea_create(ui->scrSetting_cont_month);
    lv_textarea_set_text(ui->scrSetting_ta_3, "5");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_3, "月");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_3, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_3, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_3, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_3, "0123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_3, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_3, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_3, 67, 7);
    lv_obj_set_size(ui->scrSetting_ta_3, 91, 40);
    lv_obj_add_flag(ui->scrSetting_ta_3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    //Write style for scrSetting_ta_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_3, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_3, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_3, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_3, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_3, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_3, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_3, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_cont_day
    ui->scrSetting_cont_day = lv_obj_create(ui->scrSetting_cont_time_setting);
    lv_obj_set_pos(ui->scrSetting_cont_day, 117, 101);
    lv_obj_set_size(ui->scrSetting_cont_day, 187, 63);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_day, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting_cont_day, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_day, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_day, 90, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_day, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_day, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_day, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_day, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_day, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_day, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_label_10
    ui->scrSetting_label_10 = lv_label_create(ui->scrSetting_cont_day);
    lv_label_set_text(ui->scrSetting_label_10, "日：");
    lv_label_set_long_mode(ui->scrSetting_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrSetting_label_10, 19, 16);
    lv_obj_set_size(ui->scrSetting_label_10, 40, 32);

    //Write style for scrSetting_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_label_10, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_label_10, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_4
    ui->scrSetting_ta_4 = lv_textarea_create(ui->scrSetting_cont_day);
    lv_textarea_set_text(ui->scrSetting_ta_4, "31");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_4, "日");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_4, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_4, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_4, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_4, "0123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_4, 4);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_4, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_4, 67, 7);
    lv_obj_set_size(ui->scrSetting_ta_4, 91, 40);
    lv_obj_add_flag(ui->scrSetting_ta_4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    //Write style for scrSetting_ta_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_4, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_4, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_4, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_4, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_4, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_4, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_4, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_4, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_4, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_4, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_4, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_cont_hour
    ui->scrSetting_cont_hour = lv_obj_create(ui->scrSetting_cont_time_setting);
    lv_obj_set_pos(ui->scrSetting_cont_hour, 369, 113);
    lv_obj_set_size(ui->scrSetting_cont_hour, 187, 63);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_hour, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting_cont_hour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_hour, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_hour, 90, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_hour, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_hour, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_hour, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_hour, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_hour, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_hour, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_label_11
    ui->scrSetting_label_11 = lv_label_create(ui->scrSetting_cont_hour);
    lv_label_set_text(ui->scrSetting_label_11, "时：");
    lv_label_set_long_mode(ui->scrSetting_label_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrSetting_label_11, 19, 16);
    lv_obj_set_size(ui->scrSetting_label_11, 40, 32);

    //Write style for scrSetting_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_label_11, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_label_11, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_5
    ui->scrSetting_ta_5 = lv_textarea_create(ui->scrSetting_cont_hour);
    lv_textarea_set_text(ui->scrSetting_ta_5, "12");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_5, "时");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_5, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_5, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_5, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_5, "0123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_5, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_5, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_5, 67, 7);
    lv_obj_set_size(ui->scrSetting_ta_5, 91, 40);
    lv_obj_add_flag(ui->scrSetting_ta_5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    //Write style for scrSetting_ta_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_5, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_5, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_5, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_5, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_5, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_5, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_5, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_5, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_5, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_5, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_5, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_cont_minute
    ui->scrSetting_cont_minute = lv_obj_create(ui->scrSetting_cont_time_setting);
    lv_obj_set_pos(ui->scrSetting_cont_minute, 110, 173);
    lv_obj_set_size(ui->scrSetting_cont_minute, 187, 63);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_minute, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting_cont_minute, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_minute, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_minute, 90, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_minute, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_minute, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_minute, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_minute, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_minute, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_minute, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_minute, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_minute, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_minute, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_minute, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_minute, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_label_12
    ui->scrSetting_label_12 = lv_label_create(ui->scrSetting_cont_minute);
    lv_label_set_text(ui->scrSetting_label_12, "分：");
    lv_label_set_long_mode(ui->scrSetting_label_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrSetting_label_12, 19, 16);
    lv_obj_set_size(ui->scrSetting_label_12, 40, 32);

    //Write style for scrSetting_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_label_12, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_label_12, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_label_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_6
    ui->scrSetting_ta_6 = lv_textarea_create(ui->scrSetting_cont_minute);
    lv_textarea_set_text(ui->scrSetting_ta_6, "45");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_6, "分");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_6, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_6, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_6, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_6, "0123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_6, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_6, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_6, 67, 7);
    lv_obj_set_size(ui->scrSetting_ta_6, 91, 40);
    lv_obj_add_flag(ui->scrSetting_ta_6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    //Write style for scrSetting_ta_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_6, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_6, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_6, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_6, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_6, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_6, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_6, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_6, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_6, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_6, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_6, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_cont_second
    ui->scrSetting_cont_second = lv_obj_create(ui->scrSetting_cont_time_setting);
    lv_obj_set_pos(ui->scrSetting_cont_second, 358, 210);
    lv_obj_set_size(ui->scrSetting_cont_second, 187, 63);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_second, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting_cont_second, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_second, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_second, 90, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_second, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_second, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_second, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_second, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_second, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_second, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_label_13
    ui->scrSetting_label_13 = lv_label_create(ui->scrSetting_cont_second);
    lv_label_set_text(ui->scrSetting_label_13, "秒：");
    lv_label_set_long_mode(ui->scrSetting_label_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrSetting_label_13, 19, 16);
    lv_obj_set_size(ui->scrSetting_label_13, 40, 32);

    //Write style for scrSetting_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_label_13, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_label_13, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_label_13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_7
    ui->scrSetting_ta_7 = lv_textarea_create(ui->scrSetting_cont_second);
    lv_textarea_set_text(ui->scrSetting_ta_7, "31");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_7, "秒");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_7, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_7, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_7, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_7, "0123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_7, 2);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_7, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_7, 67, 7);
    lv_obj_set_size(ui->scrSetting_ta_7, 91, 40);
    lv_obj_add_flag(ui->scrSetting_ta_7, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    //Write style for scrSetting_ta_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_7, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_7, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_7, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_7, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_7, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_7, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_7, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_7, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_7, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_7, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_7, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_btn_1
    ui->scrSetting_btn_1 = lv_btn_create(ui->scrSetting_cont_time_setting);
    ui->scrSetting_btn_1_label = lv_label_create(ui->scrSetting_btn_1);
    lv_label_set_text(ui->scrSetting_btn_1_label, "设置");
    lv_label_set_long_mode(ui->scrSetting_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scrSetting_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scrSetting_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scrSetting_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->scrSetting_btn_1, 119, 279);
    lv_obj_set_size(ui->scrSetting_btn_1, 200, 50);

    //Write style for scrSetting_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_btn_1, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_btn_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_btn_1, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_btn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->scrSetting_btn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->scrSetting_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->scrSetting_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->scrSetting_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->scrSetting_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_btn_1, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_btn_1, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_btn_2
    ui->scrSetting_btn_2 = lv_btn_create(ui->scrSetting_cont_time_setting);
    ui->scrSetting_btn_2_label = lv_label_create(ui->scrSetting_btn_2);
    lv_label_set_text(ui->scrSetting_btn_2_label, "返回");
    lv_label_set_long_mode(ui->scrSetting_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scrSetting_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scrSetting_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scrSetting_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->scrSetting_btn_2, 363, 283);
    lv_obj_set_size(ui->scrSetting_btn_2, 200, 50);

    //Write style for scrSetting_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_btn_2, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_btn_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_btn_2, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_btn_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->scrSetting_btn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->scrSetting_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->scrSetting_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->scrSetting_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->scrSetting_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_btn_2, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_btn_2, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_cont_log
    ui->scrSetting_cont_log = lv_obj_create(ui->scrSetting);
    lv_obj_set_pos(ui->scrSetting_cont_log, 44, 82);
    lv_obj_set_size(ui->scrSetting_cont_log, 712, 347);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_log, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrSetting_cont_log, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_log, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_log, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_log, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_log, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_log, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_log, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_log, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_log, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_list_3
    ui->scrSetting_list_3 = lv_list_create(ui->scrSetting_cont_log);
    ui->scrSetting_list_3_item0 = lv_list_add_btn(ui->scrSetting_list_3, LV_SYMBOL_EDIT, "日志开关");
    ui->scrSetting_list_3_item1 = lv_list_add_btn(ui->scrSetting_list_3, LV_SYMBOL_DRIVE, "最大日志数量（0-100）");
    lv_obj_set_pos(ui->scrSetting_list_3, 51, 31);
    lv_obj_set_size(ui->scrSetting_list_3, 608, 162);
    lv_obj_set_scrollbar_mode(ui->scrSetting_list_3, LV_SCROLLBAR_MODE_ACTIVE);

    //Write style state: LV_STATE_DEFAULT for &style_scrSetting_list_3_main_main_default
    static lv_style_t style_scrSetting_list_3_main_main_default;
    ui_init_style(&style_scrSetting_list_3_main_main_default);

    lv_style_set_pad_top(&style_scrSetting_list_3_main_main_default, 5);
    lv_style_set_pad_left(&style_scrSetting_list_3_main_main_default, 5);
    lv_style_set_pad_right(&style_scrSetting_list_3_main_main_default, 5);
    lv_style_set_pad_bottom(&style_scrSetting_list_3_main_main_default, 5);
    lv_style_set_bg_opa(&style_scrSetting_list_3_main_main_default, 255);
    lv_style_set_bg_color(&style_scrSetting_list_3_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_bg_grad_dir(&style_scrSetting_list_3_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_scrSetting_list_3_main_main_default, 0);
    lv_style_set_radius(&style_scrSetting_list_3_main_main_default, 0);
    lv_style_set_shadow_width(&style_scrSetting_list_3_main_main_default, 0);
    lv_obj_add_style(ui->scrSetting_list_3, &style_scrSetting_list_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_scrSetting_list_3_main_scrollbar_default
    static lv_style_t style_scrSetting_list_3_main_scrollbar_default;
    ui_init_style(&style_scrSetting_list_3_main_scrollbar_default);

    lv_style_set_radius(&style_scrSetting_list_3_main_scrollbar_default, 2);
    lv_style_set_bg_opa(&style_scrSetting_list_3_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_scrSetting_list_3_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_scrSetting_list_3_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->scrSetting_list_3, &style_scrSetting_list_3_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_scrSetting_list_3_extra_btns_main_default
    static lv_style_t style_scrSetting_list_3_extra_btns_main_default;
    ui_init_style(&style_scrSetting_list_3_extra_btns_main_default);

    lv_style_set_pad_top(&style_scrSetting_list_3_extra_btns_main_default, 10);
    lv_style_set_pad_left(&style_scrSetting_list_3_extra_btns_main_default, 20);
    lv_style_set_pad_right(&style_scrSetting_list_3_extra_btns_main_default, 10);
    lv_style_set_pad_bottom(&style_scrSetting_list_3_extra_btns_main_default, 10);
    lv_style_set_border_width(&style_scrSetting_list_3_extra_btns_main_default, 10);
    lv_style_set_border_opa(&style_scrSetting_list_3_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_scrSetting_list_3_extra_btns_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_scrSetting_list_3_extra_btns_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_scrSetting_list_3_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_scrSetting_list_3_extra_btns_main_default, &lv_font_SourceHanSerifSC_Regular_20);
    lv_style_set_text_opa(&style_scrSetting_list_3_extra_btns_main_default, 255);
    lv_style_set_radius(&style_scrSetting_list_3_extra_btns_main_default, 0);
    lv_style_set_bg_opa(&style_scrSetting_list_3_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_scrSetting_list_3_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_scrSetting_list_3_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->scrSetting_list_3_item1, &style_scrSetting_list_3_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->scrSetting_list_3_item0, &style_scrSetting_list_3_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_scrSetting_list_3_extra_texts_main_default
    static lv_style_t style_scrSetting_list_3_extra_texts_main_default;
    ui_init_style(&style_scrSetting_list_3_extra_texts_main_default);

    lv_style_set_pad_top(&style_scrSetting_list_3_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_scrSetting_list_3_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_scrSetting_list_3_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_scrSetting_list_3_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_scrSetting_list_3_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_scrSetting_list_3_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_scrSetting_list_3_extra_texts_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_scrSetting_list_3_extra_texts_main_default, 255);
    lv_style_set_radius(&style_scrSetting_list_3_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_scrSetting_list_3_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_scrSetting_list_3_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_scrSetting_list_3_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_scrSetting_list_3_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //Write codes scrSetting_sw_1
    ui->scrSetting_sw_1 = lv_switch_create(ui->scrSetting_cont_log);
    lv_obj_set_pos(ui->scrSetting_sw_1, 528, 47);
    lv_obj_set_size(ui->scrSetting_sw_1, 102, 38);

    //Write style for scrSetting_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_sw_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_sw_1, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_sw_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_sw_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->scrSetting_sw_1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->scrSetting_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->scrSetting_sw_1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for scrSetting_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_sw_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_sw_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_sw_1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes scrSetting_ta_8
    ui->scrSetting_ta_8 = lv_textarea_create(ui->scrSetting_cont_log);
    lv_textarea_set_text(ui->scrSetting_ta_8, "10");
    lv_textarea_set_placeholder_text(ui->scrSetting_ta_8, "");
    lv_textarea_set_password_bullet(ui->scrSetting_ta_8, "*");
    lv_textarea_set_password_mode(ui->scrSetting_ta_8, false);
    lv_textarea_set_one_line(ui->scrSetting_ta_8, false);
    lv_textarea_set_accepted_chars(ui->scrSetting_ta_8, "0123456789");
    lv_textarea_set_max_length(ui->scrSetting_ta_8, 3);
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->scrSetting_ta_8, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
#endif
    lv_obj_set_pos(ui->scrSetting_ta_8, 528, 107);
    lv_obj_set_size(ui->scrSetting_ta_8, 102, 38);

    //Write style for scrSetting_ta_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->scrSetting_ta_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_ta_8, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_ta_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_ta_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_ta_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_ta_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_ta_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_ta_8, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_ta_8, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_ta_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_ta_8, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_ta_8, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_ta_8, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_8, 10, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for scrSetting_ta_8, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_ta_8, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_ta_8, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_ta_8, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_ta_8, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes scrSetting_btn_4
    ui->scrSetting_btn_4 = lv_btn_create(ui->scrSetting_cont_log);
    ui->scrSetting_btn_4_label = lv_label_create(ui->scrSetting_btn_4);
    lv_label_set_text(ui->scrSetting_btn_4_label, "保存");
    lv_label_set_long_mode(ui->scrSetting_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scrSetting_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scrSetting_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scrSetting_btn_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->scrSetting_btn_4, 84, 234);
    lv_obj_set_size(ui->scrSetting_btn_4, 250, 50);

    //Write style for scrSetting_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_btn_4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_btn_4, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_btn_4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_btn_4, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_btn_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->scrSetting_btn_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->scrSetting_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->scrSetting_btn_4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->scrSetting_btn_4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->scrSetting_btn_4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_btn_4, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_btn_4, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_btn_3
    ui->scrSetting_btn_3 = lv_btn_create(ui->scrSetting_cont_log);
    ui->scrSetting_btn_3_label = lv_label_create(ui->scrSetting_btn_3);
    lv_label_set_text(ui->scrSetting_btn_3_label, "返回");
    lv_label_set_long_mode(ui->scrSetting_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scrSetting_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scrSetting_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scrSetting_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->scrSetting_btn_3, 372, 234);
    lv_obj_set_size(ui->scrSetting_btn_3, 250, 50);

    //Write style for scrSetting_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_btn_3, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_btn_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_btn_3, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_btn_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->scrSetting_btn_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->scrSetting_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->scrSetting_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->scrSetting_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->scrSetting_btn_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_btn_3, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_btn_3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_cont_line
    ui->scrSetting_cont_line = lv_obj_create(ui->scrSetting);
    lv_obj_set_pos(ui->scrSetting_cont_line, 44, 82);
    lv_obj_set_size(ui->scrSetting_cont_line, 712, 347);
    lv_obj_set_scrollbar_mode(ui->scrSetting_cont_line, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->scrSetting_cont_line, LV_OBJ_FLAG_HIDDEN);

    //Write style for scrSetting_cont_line, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_cont_line, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_cont_line, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_cont_line, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_cont_line, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_cont_line, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_cont_line, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_cont_line, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_cont_line, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_cont_line, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_line, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_line, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_line, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_cont_line, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_label_14
    ui->scrSetting_label_14 = lv_label_create(ui->scrSetting_cont_line);
    lv_label_set_text(ui->scrSetting_label_14, "待完成......");
    lv_label_set_long_mode(ui->scrSetting_label_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrSetting_label_14, 302, 125);
    lv_obj_set_size(ui->scrSetting_label_14, 100, 32);

    //Write style for scrSetting_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_label_14, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_label_14, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_label_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_label_14, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_btn_5
    ui->scrSetting_btn_5 = lv_btn_create(ui->scrSetting_cont_line);
    ui->scrSetting_btn_5_label = lv_label_create(ui->scrSetting_btn_5);
    lv_label_set_text(ui->scrSetting_btn_5_label, "返回");
    lv_label_set_long_mode(ui->scrSetting_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scrSetting_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scrSetting_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scrSetting_btn_5_label, LV_PCT(100));
    lv_obj_set_pos(ui->scrSetting_btn_5, 208, 217);
    lv_obj_set_size(ui->scrSetting_btn_5, 250, 50);

    //Write style for scrSetting_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrSetting_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrSetting_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrSetting_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrSetting_btn_5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrSetting_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrSetting_btn_5, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrSetting_btn_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrSetting_btn_5, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrSetting_btn_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->scrSetting_btn_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->scrSetting_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->scrSetting_btn_5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->scrSetting_btn_5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->scrSetting_btn_5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrSetting_btn_5, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrSetting_btn_5, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrSetting_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrSetting_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrSetting_list_1
    ui->scrSetting_list_1 = lv_list_create(ui->scrSetting);
    ui->scrSetting_list_1_item0 = lv_list_add_btn(ui->scrSetting_list_1, &_time64_alpha_30x30, "时间设置");
    ui->scrSetting_list_1_item1 = lv_list_add_btn(ui->scrSetting_list_1, LV_SYMBOL_DRIVE, "日志设置");
    ui->scrSetting_list_1_item2 = lv_list_add_btn(ui->scrSetting_list_1, LV_SYMBOL_LOOP, "线束设置");
    ui->scrSetting_list_1_item3 = lv_list_add_btn(ui->scrSetting_list_1, LV_SYMBOL_BARS, "系统状态");
    lv_obj_set_pos(ui->scrSetting_list_1, 44, 82);
    lv_obj_set_size(ui->scrSetting_list_1, 712, 347);
    lv_obj_set_scrollbar_mode(ui->scrSetting_list_1, LV_SCROLLBAR_MODE_ACTIVE);
    lv_obj_add_flag(ui->scrSetting_list_1, LV_OBJ_FLAG_HIDDEN);

    //Write style state: LV_STATE_DEFAULT for &style_scrSetting_list_1_main_main_default
    static lv_style_t style_scrSetting_list_1_main_main_default;
    ui_init_style(&style_scrSetting_list_1_main_main_default);

    lv_style_set_pad_top(&style_scrSetting_list_1_main_main_default, 5);
    lv_style_set_pad_left(&style_scrSetting_list_1_main_main_default, 5);
    lv_style_set_pad_right(&style_scrSetting_list_1_main_main_default, 5);
    lv_style_set_pad_bottom(&style_scrSetting_list_1_main_main_default, 5);
    lv_style_set_bg_opa(&style_scrSetting_list_1_main_main_default, 255);
    lv_style_set_bg_color(&style_scrSetting_list_1_main_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_bg_grad_dir(&style_scrSetting_list_1_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_scrSetting_list_1_main_main_default, 2);
    lv_style_set_border_opa(&style_scrSetting_list_1_main_main_default, 255);
    lv_style_set_border_color(&style_scrSetting_list_1_main_main_default, lv_color_hex(0x2f3243));
    lv_style_set_border_side(&style_scrSetting_list_1_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(&style_scrSetting_list_1_main_main_default, 20);
    lv_style_set_shadow_width(&style_scrSetting_list_1_main_main_default, 0);
    lv_obj_add_style(ui->scrSetting_list_1, &style_scrSetting_list_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_scrSetting_list_1_main_scrollbar_default
    static lv_style_t style_scrSetting_list_1_main_scrollbar_default;
    ui_init_style(&style_scrSetting_list_1_main_scrollbar_default);

    lv_style_set_radius(&style_scrSetting_list_1_main_scrollbar_default, 2);
    lv_style_set_bg_opa(&style_scrSetting_list_1_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_scrSetting_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_scrSetting_list_1_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->scrSetting_list_1, &style_scrSetting_list_1_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_scrSetting_list_1_extra_btns_main_default
    static lv_style_t style_scrSetting_list_1_extra_btns_main_default;
    ui_init_style(&style_scrSetting_list_1_extra_btns_main_default);

    lv_style_set_pad_top(&style_scrSetting_list_1_extra_btns_main_default, 10);
    lv_style_set_pad_left(&style_scrSetting_list_1_extra_btns_main_default, 20);
    lv_style_set_pad_right(&style_scrSetting_list_1_extra_btns_main_default, 10);
    lv_style_set_pad_bottom(&style_scrSetting_list_1_extra_btns_main_default, 10);
    lv_style_set_border_width(&style_scrSetting_list_1_extra_btns_main_default, 10);
    lv_style_set_border_opa(&style_scrSetting_list_1_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_scrSetting_list_1_extra_btns_main_default, lv_color_hex(0xe1e6ee));
    lv_style_set_border_side(&style_scrSetting_list_1_extra_btns_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_scrSetting_list_1_extra_btns_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_scrSetting_list_1_extra_btns_main_default, &lv_font_SourceHanSerifSC_Regular_25);
    lv_style_set_text_opa(&style_scrSetting_list_1_extra_btns_main_default, 255);
    lv_style_set_radius(&style_scrSetting_list_1_extra_btns_main_default, 0);
    lv_style_set_bg_opa(&style_scrSetting_list_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_scrSetting_list_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_scrSetting_list_1_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->scrSetting_list_1_item3, &style_scrSetting_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->scrSetting_list_1_item2, &style_scrSetting_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->scrSetting_list_1_item1, &style_scrSetting_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->scrSetting_list_1_item0, &style_scrSetting_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_scrSetting_list_1_extra_texts_main_default
    static lv_style_t style_scrSetting_list_1_extra_texts_main_default;
    ui_init_style(&style_scrSetting_list_1_extra_texts_main_default);

    lv_style_set_pad_top(&style_scrSetting_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_scrSetting_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_scrSetting_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_scrSetting_list_1_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_scrSetting_list_1_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_scrSetting_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_scrSetting_list_1_extra_texts_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_scrSetting_list_1_extra_texts_main_default, 255);
    lv_style_set_radius(&style_scrSetting_list_1_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_scrSetting_list_1_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_scrSetting_list_1_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_scrSetting_list_1_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_scrSetting_list_1_extra_texts_main_default, LV_GRAD_DIR_NONE);

    //The custom code of scrSetting.
    custom_scr_setting_init(&guider_ui);
    lv_obj_clear_flag(guider_ui.scrSetting_cont_log, LV_OBJ_FLAG_SCROLLABLE);


    //Update current screen layout.
    lv_obj_update_layout(ui->scrSetting);

    //Init events for screen.
    events_init_scrSetting(ui);
}
