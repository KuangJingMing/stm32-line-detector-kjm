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



void setup_scr_screenLog(lv_ui *ui)
{
    //Write codes screenLog
    ui->screenLog = lv_obj_create(NULL);
    lv_obj_set_size(ui->screenLog, 800, 480);
    lv_obj_set_scrollbar_mode(ui->screenLog, LV_SCROLLBAR_MODE_OFF);

    //Write style for screenLog, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screenLog, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screenLog, lv_color_hex(0xF3F8FE), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screenLog, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screenLog_contBG
    ui->screenLog_contBG = lv_obj_create(ui->screenLog);
    lv_obj_set_pos(ui->screenLog_contBG, 0, 0);
    lv_obj_set_size(ui->screenLog_contBG, 800, 105);
    lv_obj_set_scrollbar_mode(ui->screenLog_contBG, LV_SCROLLBAR_MODE_OFF);

    //Write style for screenLog_contBG, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screenLog_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screenLog_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screenLog_contBG, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screenLog_contBG, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screenLog_contBG, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screenLog_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screenLog_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screenLog_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screenLog_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screenLog_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screenLog_rizh
    ui->screenLog_rizh = lv_label_create(ui->screenLog);
    lv_label_set_text(ui->screenLog_rizh, "日志模式");
    lv_label_set_long_mode(ui->screenLog_rizh, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screenLog_rizh, 225, 40);
    lv_obj_set_size(ui->screenLog_rizh, 350, 56);

    //Write style for screenLog_rizh, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screenLog_rizh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screenLog_rizh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screenLog_rizh, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screenLog_rizh, &lv_font_SourceHanSerifSC_Regular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screenLog_rizh, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screenLog_rizh, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screenLog_rizh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screenLog_rizh, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screenLog_rizh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screenLog_rizh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screenLog_rizh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screenLog_rizh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screenLog_rizh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screenLog_rizh, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screenLog_btnBack
    ui->screenLog_btnBack = lv_btn_create(ui->screenLog);
    ui->screenLog_btnBack_label = lv_label_create(ui->screenLog_btnBack);
    lv_label_set_text(ui->screenLog_btnBack_label, "<");
    lv_label_set_long_mode(ui->screenLog_btnBack_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screenLog_btnBack_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screenLog_btnBack, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screenLog_btnBack_label, LV_PCT(100));
    lv_obj_set_pos(ui->screenLog_btnBack, 41, 30);
    lv_obj_set_size(ui->screenLog_btnBack, 58, 56);

    //Write style for screenLog_btnBack, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screenLog_btnBack, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screenLog_btnBack, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screenLog_btnBack, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screenLog_btnBack, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screenLog_btnBack, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screenLog_btnBack, &lv_font_montserratMedium_41, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screenLog_btnBack, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screenLog_btnBack, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screenLog_cont_list
    ui->screenLog_cont_list = lv_obj_create(ui->screenLog);
    lv_obj_set_pos(ui->screenLog_cont_list, 44, 82);
    lv_obj_set_size(ui->screenLog_cont_list, 712, 347);
    lv_obj_set_scrollbar_mode(ui->screenLog_cont_list, LV_SCROLLBAR_MODE_OFF);

    //Write style for screenLog_cont_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screenLog_cont_list, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screenLog_cont_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screenLog_cont_list, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screenLog_cont_list, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screenLog_cont_list, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screenLog_cont_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screenLog_cont_list, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screenLog_cont_list, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screenLog_cont_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screenLog_cont_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screenLog_cont_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screenLog_cont_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screenLog_cont_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screenLog.


    //Update current screen layout.
    lv_obj_update_layout(ui->screenLog);

    //Init events for screen.
    events_init_screenLog(ui);
}
