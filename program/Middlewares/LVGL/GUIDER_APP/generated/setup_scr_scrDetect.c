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



void setup_scr_scrDetect(lv_ui *ui)
{
    //Write codes scrDetect
    ui->scrDetect = lv_obj_create(NULL);
    lv_obj_set_size(ui->scrDetect, 800, 480);
    lv_obj_set_scrollbar_mode(ui->scrDetect, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrDetect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrDetect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrDetect, lv_color_hex(0xF3F8FE), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrDetect, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_contBG
    ui->scrDetect_contBG = lv_obj_create(ui->scrDetect);
    lv_obj_set_pos(ui->scrDetect_contBG, 0, 0);
    lv_obj_set_size(ui->scrDetect_contBG, 800, 105);
    lv_obj_set_scrollbar_mode(ui->scrDetect_contBG, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrDetect_contBG, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_contBG, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrDetect_contBG, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrDetect_contBG, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_contBG, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_btn_1
    ui->scrDetect_btn_1 = lv_btn_create(ui->scrDetect_contBG);
    ui->scrDetect_btn_1_label = lv_label_create(ui->scrDetect_btn_1);
    lv_label_set_text(ui->scrDetect_btn_1_label, "<");
    lv_label_set_long_mode(ui->scrDetect_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->scrDetect_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->scrDetect_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->scrDetect_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->scrDetect_btn_1, 41, 30);
    lv_obj_set_size(ui->scrDetect_btn_1, 58, 56);

    //Write style for scrDetect_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrDetect_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->scrDetect_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_btn_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrDetect_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrDetect_btn_1, &lv_font_montserratMedium_41, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrDetect_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrDetect_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_label_1
    ui->scrDetect_label_1 = lv_label_create(ui->scrDetect);
    lv_label_set_text(ui->scrDetect_label_1, "请选择要检测的线束");
    lv_label_set_long_mode(ui->scrDetect_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrDetect_label_1, 225, 40);
    lv_obj_set_size(ui->scrDetect_label_1, 350, 56);

    //Write style for scrDetect_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrDetect_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrDetect_label_1, &lv_font_SourceHanSerifSC_Regular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrDetect_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrDetect_label_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrDetect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrDetect_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_cont_1
    ui->scrDetect_cont_1 = lv_obj_create(ui->scrDetect);
    lv_obj_set_pos(ui->scrDetect_cont_1, 44, 82);
    lv_obj_set_size(ui->scrDetect_cont_1, 712, 347);
    lv_obj_set_scrollbar_mode(ui->scrDetect_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrDetect_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->scrDetect_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->scrDetect_cont_1, lv_color_hex(0x2f3243), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->scrDetect_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_cont_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrDetect_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrDetect_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_cont_5
    ui->scrDetect_cont_5 = lv_obj_create(ui->scrDetect_cont_1);
    lv_obj_set_pos(ui->scrDetect_cont_5, 10, 75);
    lv_obj_set_size(ui->scrDetect_cont_5, 166, 211);
    lv_obj_set_scrollbar_mode(ui->scrDetect_cont_5, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrDetect_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrDetect_cont_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrDetect_cont_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->scrDetect_cont_5, &_btn_bg_4_166x211, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->scrDetect_cont_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->scrDetect_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_img_4
    ui->scrDetect_img_4 = lv_img_create(ui->scrDetect_cont_5);
    lv_obj_add_flag(ui->scrDetect_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->scrDetect_img_4, &_line_2_alpha_66x66);
    lv_img_set_pivot(ui->scrDetect_img_4, 50,50);
    lv_img_set_angle(ui->scrDetect_img_4, 0);
    lv_obj_set_pos(ui->scrDetect_img_4, 75, 33);
    lv_obj_set_size(ui->scrDetect_img_4, 66, 66);
    lv_obj_add_flag(ui->scrDetect_img_4, LV_OBJ_FLAG_EVENT_BUBBLE);

    //Write style for scrDetect_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->scrDetect_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->scrDetect_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->scrDetect_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_label_5
    ui->scrDetect_label_5 = lv_label_create(ui->scrDetect_cont_5);
    lv_label_set_text(ui->scrDetect_label_5, "样本线束");
    lv_label_set_long_mode(ui->scrDetect_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrDetect_label_5, 10, 157);
    lv_obj_set_size(ui->scrDetect_label_5, 128, 33);
    lv_obj_add_flag(ui->scrDetect_label_5, LV_OBJ_FLAG_EVENT_BUBBLE);

    //Write style for scrDetect_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrDetect_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrDetect_label_5, &lv_font_SourceHanSerifSC_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrDetect_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrDetect_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_cont_2
    ui->scrDetect_cont_2 = lv_obj_create(ui->scrDetect_cont_1);
    lv_obj_set_pos(ui->scrDetect_cont_2, 174, 75);
    lv_obj_set_size(ui->scrDetect_cont_2, 159, 214);
    lv_obj_set_scrollbar_mode(ui->scrDetect_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrDetect_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrDetect_cont_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrDetect_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->scrDetect_cont_2, &_btn_bg_1_159x214, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->scrDetect_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->scrDetect_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_img_1
    ui->scrDetect_img_1 = lv_img_create(ui->scrDetect_cont_2);
    lv_obj_add_flag(ui->scrDetect_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->scrDetect_img_1, &_line_2_alpha_80x90);
    lv_img_set_pivot(ui->scrDetect_img_1, 50,50);
    lv_img_set_angle(ui->scrDetect_img_1, 0);
    lv_obj_set_pos(ui->scrDetect_img_1, 75, 33);
    lv_obj_set_size(ui->scrDetect_img_1, 80, 90);
    lv_obj_add_flag(ui->scrDetect_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);

    //Write style for scrDetect_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->scrDetect_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->scrDetect_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->scrDetect_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_label_2
    ui->scrDetect_label_2 = lv_label_create(ui->scrDetect_cont_2);
    lv_label_set_text(ui->scrDetect_label_2, "TEB8283-42");
    lv_label_set_long_mode(ui->scrDetect_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrDetect_label_2, 10, 157);
    lv_obj_set_size(ui->scrDetect_label_2, 128, 33);
    lv_obj_add_flag(ui->scrDetect_label_2, LV_OBJ_FLAG_EVENT_BUBBLE);

    //Write style for scrDetect_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrDetect_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrDetect_label_2, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrDetect_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrDetect_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_cont_3
    ui->scrDetect_cont_3 = lv_obj_create(ui->scrDetect_cont_1);
    lv_obj_set_pos(ui->scrDetect_cont_3, 353, 75);
    lv_obj_set_size(ui->scrDetect_cont_3, 159, 214);
    lv_obj_set_scrollbar_mode(ui->scrDetect_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrDetect_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrDetect_cont_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrDetect_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->scrDetect_cont_3, &_btn_bg_2_159x214, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->scrDetect_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->scrDetect_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_img_2
    ui->scrDetect_img_2 = lv_img_create(ui->scrDetect_cont_3);
    lv_obj_add_flag(ui->scrDetect_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->scrDetect_img_2, &_line_2_alpha_80x90);
    lv_img_set_pivot(ui->scrDetect_img_2, 50,50);
    lv_img_set_angle(ui->scrDetect_img_2, 0);
    lv_obj_set_pos(ui->scrDetect_img_2, 75, 33);
    lv_obj_set_size(ui->scrDetect_img_2, 80, 90);
    lv_obj_add_flag(ui->scrDetect_img_2, LV_OBJ_FLAG_EVENT_BUBBLE);

    //Write style for scrDetect_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->scrDetect_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->scrDetect_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->scrDetect_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_label_3
    ui->scrDetect_label_3 = lv_label_create(ui->scrDetect_cont_3);
    lv_label_set_text(ui->scrDetect_label_3, "TEG5951-47");
    lv_label_set_long_mode(ui->scrDetect_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrDetect_label_3, 10, 157);
    lv_obj_set_size(ui->scrDetect_label_3, 128, 33);
    lv_obj_add_flag(ui->scrDetect_label_3, LV_OBJ_FLAG_EVENT_BUBBLE);

    //Write style for scrDetect_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrDetect_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrDetect_label_3, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrDetect_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrDetect_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_cont_4
    ui->scrDetect_cont_4 = lv_obj_create(ui->scrDetect_cont_1);
    lv_obj_set_pos(ui->scrDetect_cont_4, 526, 76);
    lv_obj_set_size(ui->scrDetect_cont_4, 159, 214);
    lv_obj_set_scrollbar_mode(ui->scrDetect_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrDetect_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrDetect_cont_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrDetect_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->scrDetect_cont_4, &_btn_bg_3_159x214, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->scrDetect_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->scrDetect_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_img_3
    ui->scrDetect_img_3 = lv_img_create(ui->scrDetect_cont_4);
    lv_obj_add_flag(ui->scrDetect_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->scrDetect_img_3, &_line_2_alpha_80x90);
    lv_img_set_pivot(ui->scrDetect_img_3, 50,50);
    lv_img_set_angle(ui->scrDetect_img_3, 0);
    lv_obj_set_pos(ui->scrDetect_img_3, 75, 33);
    lv_obj_set_size(ui->scrDetect_img_3, 80, 90);
    lv_obj_add_flag(ui->scrDetect_img_3, LV_OBJ_FLAG_EVENT_BUBBLE);

    //Write style for scrDetect_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->scrDetect_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->scrDetect_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->scrDetect_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrDetect_label_4
    ui->scrDetect_label_4 = lv_label_create(ui->scrDetect_cont_4);
    lv_label_set_text(ui->scrDetect_label_4, "TEG-100");
    lv_label_set_long_mode(ui->scrDetect_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrDetect_label_4, 10, 157);
    lv_obj_set_size(ui->scrDetect_label_4, 128, 33);
    lv_obj_add_flag(ui->scrDetect_label_4, LV_OBJ_FLAG_EVENT_BUBBLE);

    //Write style for scrDetect_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrDetect_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrDetect_label_4, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrDetect_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrDetect_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrDetect_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of scrDetect.
    custom_scr_detect_init(&guider_ui);

    //Update current screen layout.
    lv_obj_update_layout(ui->scrDetect);

    //Init events for screen.
    events_init_scrDetect(ui);
}
