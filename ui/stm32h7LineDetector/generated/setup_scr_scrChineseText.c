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



void setup_scr_scrChineseText(lv_ui *ui)
{
    //Write codes scrChineseText
    ui->scrChineseText = lv_obj_create(NULL);
    lv_obj_set_size(ui->scrChineseText, 800, 480);
    lv_obj_set_scrollbar_mode(ui->scrChineseText, LV_SCROLLBAR_MODE_OFF);

    //Write style for scrChineseText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->scrChineseText, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->scrChineseText, lv_color_hex(0xc1d2ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->scrChineseText, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrChineseText_label_1
    ui->scrChineseText_label_1 = lv_label_create(ui->scrChineseText);
    lv_label_set_text(ui->scrChineseText_label_1, "金样学习完成检测正在中请稍后功线时间本数据");
    lv_label_set_long_mode(ui->scrChineseText_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrChineseText_label_1, 31, 24);
    lv_obj_set_size(ui->scrChineseText_label_1, 340, 34);

    //Write style for scrChineseText_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrChineseText_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrChineseText_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrChineseText_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrChineseText_label_1, &lv_font_SourceHanSerifSC_Regular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrChineseText_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrChineseText_label_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrChineseText_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrChineseText_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrChineseText_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrChineseText_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrChineseText_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrChineseText_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrChineseText_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrChineseText_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrChineseText_label_2
    ui->scrChineseText_label_2 = lv_label_create(ui->scrChineseText);
    lv_label_set_text(ui->scrChineseText_label_2, "错误警告年月日时分秒日期：");
    lv_label_set_long_mode(ui->scrChineseText_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrChineseText_label_2, 127, 92);
    lv_obj_set_size(ui->scrChineseText_label_2, 136, 37);

    //Write style for scrChineseText_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrChineseText_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrChineseText_label_2, &lv_font_SourceHanSerifSC_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrChineseText_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrChineseText_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrChineseText_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrChineseText_label_3
    ui->scrChineseText_label_3 = lv_label_create(ui->scrChineseText);
    lv_label_set_text(ui->scrChineseText_label_3, "结果: 系统启动完成设备正常运行日志：错位短路断年月时间小分钟秒检测到个警告");
    lv_label_set_long_mode(ui->scrChineseText_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrChineseText_label_3, 24, 160);
    lv_obj_set_size(ui->scrChineseText_label_3, 343, 37);

    //Write style for scrChineseText_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrChineseText_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrChineseText_label_3, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrChineseText_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrChineseText_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrChineseText_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes scrChineseText_label_4
    ui->scrChineseText_label_4 = lv_label_create(ui->scrChineseText);
    lv_label_set_text(ui->scrChineseText_label_4, "结果: 结果全局变量定义引脚映射表数线束检测器初始化输出锁存入配金样学习成功置参清空响法应模式关系（自动）逐一激励每个端进行设所有为高电平默认状态只将当前低到延时稳读取分析，寻找对的示连通判断逻辑正常：恢复完以上率验证编号效性制改比较函首先不匹假已排序便于简单冒泡收集记录统计包括短路情况防止组越界位掩码仅支持调试列用标经处理过查是否在多可能具相同其他使主打印信息或无后续中修第步二三故障类型、错非期望接生报告缓冲区大小实际写字符头部总开详细涉及影算合格快速指获等待户准备品执循环下次此添加交互针重✓失败✗");
    lv_label_set_long_mode(ui->scrChineseText_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->scrChineseText_label_4, 31, 271);
    lv_obj_set_size(ui->scrChineseText_label_4, 329, 37);

    //Write style for scrChineseText_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->scrChineseText_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->scrChineseText_label_4, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->scrChineseText_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->scrChineseText_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->scrChineseText_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of scrChineseText.


    //Update current screen layout.
    lv_obj_update_layout(ui->scrChineseText);

}
