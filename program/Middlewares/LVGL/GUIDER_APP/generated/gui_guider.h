/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *scrHome;
	bool scrHome_del;
	lv_obj_t *scrHome_contBG;
	lv_obj_t *scrHome_contMain;
	lv_obj_t *scrHome_contSetup;
	lv_obj_t *scrHome_imgIconSetup;
	lv_obj_t *scrHome_labelSetup;
	lv_obj_t *scrHome_contPrint;
	lv_obj_t *scrHome_imgIconPrint;
	lv_obj_t *scrHome_labelPrint;
	lv_obj_t *scrHome_contCopy;
	lv_obj_t *scrHome_imgIconCopy;
	lv_obj_t *scrHome_labelCopy;
	lv_obj_t *scrHome_contScan;
	lv_obj_t *scrHome_imgIconScan;
	lv_obj_t *scrHome_labelScan;
	lv_obj_t *scrHome_contTop;
	lv_obj_t *scrHome_imgIconWIFI;
	lv_obj_t *scrHome_imgIconCall;
	lv_obj_t *scrHome_imgIconEco;
	lv_obj_t *scrHome_imgIconPC;
	lv_obj_t *scrHome_labelDate;
	lv_obj_t *scrHome_labelPrompt;
	lv_obj_t *scrHome_contColorInk;
	lv_obj_t *scrHome_barBlueInk;
	lv_obj_t *scrHome_barRedInk;
	lv_obj_t *scrHome_barYellowInk;
	lv_obj_t *scrHome_barBlackInk;
	lv_obj_t *scrComplete;
	bool scrComplete_del;
	lv_obj_t *scrComplete_contBG;
	lv_obj_t *scrComplete_labelTitle;
	lv_obj_t *scrComplete_btnBack;
	lv_obj_t *scrComplete_btnBack_label;
	lv_obj_t *scrComplete_ta_1;
	lv_obj_t *scrLoader;
	bool scrLoader_del;
	lv_obj_t *scrLoader_contBG;
	lv_obj_t *scrLoader_arcLoader;
	lv_obj_t *scrLoader_tpLoader;
	lv_obj_t *scrLoader_labelPrompt;
	lv_obj_t *scrLog;
	bool scrLog_del;
	lv_obj_t *scrLog_contBG;
	lv_obj_t *scrLog_rizh;
	lv_obj_t *scrLog_btnBack;
	lv_obj_t *scrLog_btnBack_label;
	lv_obj_t *scrLog_cont_list;
	lv_obj_t *scrSetting;
	bool scrSetting_del;
	lv_obj_t *scrSetting_contBG;
	lv_obj_t *scrSetting_labelTitle;
	lv_obj_t *scrSetting_btnBack;
	lv_obj_t *scrSetting_btnBack_label;
	lv_obj_t *scrSetting_cont_time_setting;
	lv_obj_t *scrSetting_cont_year;
	lv_obj_t *scrSetting_label_8;
	lv_obj_t *scrSetting_ta_2;
	lv_obj_t *scrSetting_cont_month;
	lv_obj_t *scrSetting_label_9;
	lv_obj_t *scrSetting_ta_3;
	lv_obj_t *scrSetting_cont_day;
	lv_obj_t *scrSetting_label_10;
	lv_obj_t *scrSetting_ta_4;
	lv_obj_t *scrSetting_cont_hour;
	lv_obj_t *scrSetting_label_11;
	lv_obj_t *scrSetting_ta_5;
	lv_obj_t *scrSetting_cont_minute;
	lv_obj_t *scrSetting_label_12;
	lv_obj_t *scrSetting_ta_6;
	lv_obj_t *scrSetting_cont_second;
	lv_obj_t *scrSetting_label_13;
	lv_obj_t *scrSetting_ta_7;
	lv_obj_t *scrSetting_btn_1;
	lv_obj_t *scrSetting_btn_1_label;
	lv_obj_t *scrSetting_btn_2;
	lv_obj_t *scrSetting_btn_2_label;
	lv_obj_t *scrSetting_cont_log;
	lv_obj_t *scrSetting_list_3;
	lv_obj_t *scrSetting_list_3_item0;
	lv_obj_t *scrSetting_list_3_item1;
	lv_obj_t *scrSetting_sw_1;
	lv_obj_t *scrSetting_ta_8;
	lv_obj_t *scrSetting_btn_4;
	lv_obj_t *scrSetting_btn_4_label;
	lv_obj_t *scrSetting_btn_3;
	lv_obj_t *scrSetting_btn_3_label;
	lv_obj_t *scrSetting_cont_line;
	lv_obj_t *scrSetting_label_14;
	lv_obj_t *scrSetting_btn_5;
	lv_obj_t *scrSetting_btn_5_label;
	lv_obj_t *scrSetting_cont_sys;
	lv_obj_t *scrSetting_btnm_1;
	lv_obj_t *scrSetting_btn_6;
	lv_obj_t *scrSetting_btn_6_label;
	lv_obj_t *scrSetting_list_1;
	lv_obj_t *scrSetting_list_1_item0;
	lv_obj_t *scrSetting_list_1_item1;
	lv_obj_t *scrSetting_list_1_item2;
	lv_obj_t *scrSetting_list_1_item3;
	lv_obj_t *scrDetect;
	bool scrDetect_del;
	lv_obj_t *scrDetect_contBG;
	lv_obj_t *scrDetect_btn_1;
	lv_obj_t *scrDetect_btn_1_label;
	lv_obj_t *scrDetect_label_1;
	lv_obj_t *scrDetect_cont_1;
	lv_obj_t *scrDetect_cont_5;
	lv_obj_t *scrDetect_img_4;
	lv_obj_t *scrDetect_label_5;
	lv_obj_t *scrDetect_cont_2;
	lv_obj_t *scrDetect_img_1;
	lv_obj_t *scrDetect_label_2;
	lv_obj_t *scrDetect_cont_3;
	lv_obj_t *scrDetect_img_2;
	lv_obj_t *scrDetect_label_3;
	lv_obj_t *scrDetect_cont_4;
	lv_obj_t *scrDetect_img_3;
	lv_obj_t *scrDetect_label_4;
	lv_obj_t *scrChineseText;
	bool scrChineseText_del;
	lv_obj_t *scrChineseText_label_1;
	lv_obj_t *scrChineseText_label_2;
	lv_obj_t *scrChineseText_label_3;
	lv_obj_t *scrChineseText_label_4;
	lv_obj_t *g_kb_top_layer;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_scrHome(lv_ui *ui);
void setup_scr_scrComplete(lv_ui *ui);
void setup_scr_scrLoader(lv_ui *ui);
void setup_scr_scrLog(lv_ui *ui);
void setup_scr_scrSetting(lv_ui *ui);
void setup_scr_scrDetect(lv_ui *ui);
void setup_scr_scrChineseText(lv_ui *ui);

LV_IMG_DECLARE(_btn_bg_4_166x211);
LV_IMG_DECLARE(_setup_alpha_66x66);

LV_IMG_DECLARE(_btn_bg_3_166x211);
LV_IMG_DECLARE(_print_alpha_66x66);

LV_IMG_DECLARE(_btn_bg_1_166x211);
LV_IMG_DECLARE(_copy_alpha_61x70);

LV_IMG_DECLARE(_btn_bg_2_166x211);
LV_IMG_DECLARE(_scan_alpha_61x70);
LV_IMG_DECLARE(_wifi_alpha_55x44);
LV_IMG_DECLARE(_tel_alpha_46x42);
LV_IMG_DECLARE(_eco_alpha_48x38);
LV_IMG_DECLARE(_pc_alpha_50x42);
LV_IMG_DECLARE(_time64_alpha_30x30);

LV_IMG_DECLARE(_btn_bg_4_166x211);
LV_IMG_DECLARE(_line_2_alpha_66x66);

LV_IMG_DECLARE(_btn_bg_1_159x214);
LV_IMG_DECLARE(_line_2_alpha_80x90);

LV_IMG_DECLARE(_btn_bg_2_159x214);
LV_IMG_DECLARE(_line_2_alpha_80x90);

LV_IMG_DECLARE(_btn_bg_3_159x214);
LV_IMG_DECLARE(_line_2_alpha_80x90);

LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_25)
LV_FONT_DECLARE(lv_font_montserratMedium_26)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_23)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_33)
LV_FONT_DECLARE(lv_font_montserratMedium_41)
LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_33)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_20)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_12)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_Abel_regular_20)


#ifdef __cplusplus
}
#endif
#endif
