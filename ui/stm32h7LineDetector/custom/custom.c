/*
Copyright 2023 NXP

NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
terms, then you may not retain, install, activate or otherwise use the software.
*/

/*********************
INCLUDES
*********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include <string.h>
#include "gui_guider.h"
#include <stdlib.h> // for atoi

/*********************
DEFINES
*********************/
#define MAX_LOGS 10

/**********************
TYPEDEFS
**********************/
typedef struct {
    char text[100];           // 日志文本
    lv_obj_t *item_obj;      // 对应的UI对象
    int index;               // 日志索引
} log_item_t;

/**********************
STATIC PROTOTYPES
**********************/
static void item_hover_handler(lv_event_t *e);
static void delete_btn_handler(lv_event_t *e);

/**********************
STATIC VARIABLES
**********************/
// 日志相关样式变量
static lv_style_t list_style;
static lv_style_t item_style;
static lv_style_t item_hover_style;
static lv_style_t text_style;
static lv_style_t scrollbar_style;
static lv_style_t delete_btn_style;
static lv_style_t delete_btn_hover_style;

// 日志数据变量
static log_item_t log_items[MAX_LOGS];
static int log_count = 0;
static int next_index = 1;
static lv_obj_t *log_list;
static SCREEN_MODE current_mode; 


void custom_scr_setting_init(lv_ui *ui) {
    // scrSetting_cont_time_setting START
    // 将主容器设为flex布局
    lv_obj_set_layout(ui->scrSetting_cont_time_setting, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(ui->scrSetting_cont_time_setting, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui->scrSetting_cont_time_setting, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    // 禁用滚动功能 - 让控件固定不动
    lv_obj_clear_flag(ui->scrSetting_cont_time_setting, LV_OBJ_FLAG_SCROLLABLE);
    // 容器的内边距 - 让控件远离容器边界
    lv_obj_set_style_pad_top(ui->scrSetting_cont_time_setting, 40, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui->scrSetting_cont_time_setting, 40, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui->scrSetting_cont_time_setting, 35, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui->scrSetting_cont_time_setting, 35, LV_PART_MAIN);
    // 控件之间的间距
    lv_obj_set_style_pad_row(ui->scrSetting_cont_time_setting, 20, LV_PART_MAIN);      // 行间距
    lv_obj_set_style_pad_column(ui->scrSetting_cont_time_setting, 65, LV_PART_MAIN);   // 列间距
    // scrSetting_cont_time_setting END

    // scrSetting_cont_log START
    // 禁用滚动功能 - 让控件固定不动
    lv_obj_clear_flag(ui->scrSetting_cont_log, LV_OBJ_FLAG_SCROLLABLE);
    // scrSetting_cont_log END

    // scrSetting_cont_line START
    lv_obj_set_layout(ui->scrSetting_cont_line, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(ui->scrSetting_cont_line, LV_FLEX_FLOW_COLUMN);  // 改为列布局
    lv_obj_set_flex_align(ui->scrSetting_cont_line, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);  // 主轴、交叉轴、内容都居中
    // scrSetting_cont_line END
}

void custom_scr_detect_init(lv_ui *ui) {
    
    lv_obj_set_layout(ui->scrDetect_cont_1, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(ui->scrDetect_cont_1, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui->scrDetect_cont_1, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    
    // 禁用滚动功能 - 让控件固定不动
    lv_obj_clear_flag(ui->scrDetect_cont_1, LV_OBJ_FLAG_SCROLLABLE);
    
    // 容器的内边距 - 让控件远离容器边界
    lv_obj_set_style_pad_top(ui->scrDetect_cont_1, 5, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(ui->scrDetect_cont_1, 5, LV_PART_MAIN);
    lv_obj_set_style_pad_left(ui->scrDetect_cont_1, 5, LV_PART_MAIN);
    lv_obj_set_style_pad_right(ui->scrDetect_cont_1, 5, LV_PART_MAIN);
    
    // 控件之间的间距
    lv_obj_set_style_pad_row(ui->scrDetect_cont_1, 5, LV_PART_MAIN);      // 行间距
    lv_obj_set_style_pad_column(ui->scrDetect_cont_1, 5, LV_PART_MAIN);   // 列间距
    
   
}

// 重新加载所有墨水条动画
void reload_ink_bar_animations(lv_ui *ui) {
    // 先清除可能存在的动画
    lv_anim_del(ui->scrHome_barBlueInk, NULL);
    lv_anim_del(ui->scrHome_barRedInk, NULL);
    lv_anim_del(ui->scrHome_barYellowInk, NULL);
    lv_anim_del(ui->scrHome_barBlackInk, NULL);
    
    // 设置为0（无动画）
    lv_bar_set_value(ui->scrHome_barBlueInk, 0, LV_ANIM_OFF);
    lv_bar_set_value(ui->scrHome_barRedInk, 0, LV_ANIM_OFF);
    lv_bar_set_value(ui->scrHome_barYellowInk, 0, LV_ANIM_OFF);
    lv_bar_set_value(ui->scrHome_barBlackInk, 0, LV_ANIM_OFF);
    
    // 刷新显示
    lv_refr_now(NULL);
    
    // 设置目标值（有动画）
    lv_bar_set_value(ui->scrHome_barBlueInk, 80, LV_ANIM_ON);
    lv_bar_set_value(ui->scrHome_barRedInk, 25, LV_ANIM_ON);
    lv_bar_set_value(ui->scrHome_barYellowInk, 70, LV_ANIM_ON);
    lv_bar_set_value(ui->scrHome_barBlackInk, 55, LV_ANIM_ON);
}


/**
@brief Create a demo application
*/
void custom_init(lv_ui *ui)
{

}

void set_screen_mode(SCREEN_MODE mode) {
    current_mode = mode;
}

SCREEN_MODE get_current_mode(void) {
    return current_mode;
}

/**
@brief       查找日志项索引
@param       index: 日志索引
@retval      日志项在数组中的位置，-1表示未找到
*/
static int find_log_item_by_index(int index)
{
    for (int i = 0; i < log_count; i++) {
        if (log_items[i].index == index) {
            return i;
        }
    }
    return -1;
}

/**
@brief       初始化样式
@param       无
@retval      无
*/
static void init_styles(void)
{
    // 列表样式
    lv_style_init(&list_style);
    lv_style_set_bg_color(&list_style, lv_color_hex(0xF8F9FA));
    lv_style_set_bg_opa(&list_style, 255);
    lv_style_set_border_width(&list_style, 1);
    lv_style_set_border_color(&list_style, lv_color_hex(0xE9ECEF));
    lv_style_set_border_opa(&list_style, 255);
    lv_style_set_radius(&list_style, 8);
    lv_style_set_pad_all(&list_style, 8);
    lv_style_set_pad_gap(&list_style, 5);

    // 滚动条样式
    lv_style_init(&scrollbar_style);
    lv_style_set_bg_color(&scrollbar_style, lv_color_hex(0x6C757D));
    lv_style_set_bg_opa(&scrollbar_style, 180);
    lv_style_set_width(&scrollbar_style, 6);
    lv_style_set_radius(&scrollbar_style, 3);

    // 日志项样式
    lv_style_init(&item_style);
    lv_style_set_bg_color(&item_style, lv_color_hex(0xFFFFFF));
    lv_style_set_bg_opa(&item_style, 255);
    lv_style_set_border_color(&item_style, lv_color_hex(0xDEE2E6));
    lv_style_set_border_width(&item_style, 1);
    lv_style_set_border_opa(&item_style, 255);
    lv_style_set_radius(&item_style, 6);
    lv_style_set_shadow_color(&item_style, lv_color_hex(0x000000));
    lv_style_set_shadow_width(&item_style, 2);
    lv_style_set_shadow_opa(&item_style, 20);
    lv_style_set_shadow_ofs_x(&item_style, 0);
    lv_style_set_shadow_ofs_y(&item_style, 1);
    lv_style_set_pad_all(&item_style, 12);

    // 日志项悬停样式
    lv_style_init(&item_hover_style);
    lv_style_set_bg_color(&item_hover_style, lv_color_hex(0xF8F9FA));
    lv_style_set_border_color(&item_hover_style, lv_color_hex(0x007BFF));
    lv_style_set_shadow_width(&item_hover_style, 4);
    lv_style_set_shadow_opa(&item_hover_style, 40);

    // 文本样式
    lv_style_init(&text_style);
    lv_style_set_text_font(&text_style, &lv_font_SourceHanSerifSC_Regular_20);
    lv_style_set_text_color(&text_style, lv_color_hex(0x212529));
    lv_style_set_text_line_space(&text_style, 2);

    // 删除按钮样式
    lv_style_init(&delete_btn_style);
    lv_style_set_bg_color(&delete_btn_style, lv_color_hex(0xDC3545));
    lv_style_set_bg_opa(&delete_btn_style, 255);
    lv_style_set_radius(&delete_btn_style, 15);
    lv_style_set_border_width(&delete_btn_style, 0);
    lv_style_set_shadow_color(&delete_btn_style, lv_color_hex(0xDC3545));
    lv_style_set_shadow_width(&delete_btn_style, 2);
    lv_style_set_shadow_opa(&delete_btn_style, 50);

    // 删除按钮悬停样式
    lv_style_init(&delete_btn_hover_style);
    lv_style_set_bg_color(&delete_btn_hover_style, lv_color_hex(0xC82333));
    lv_style_set_shadow_width(&delete_btn_hover_style, 4);
    lv_style_set_shadow_opa(&delete_btn_hover_style, 80);
    
    lv_style_set_transform_zoom(&delete_btn_hover_style, 186);
}

/**
@brief       日志项悬停事件处理
@param       e: 事件数据
@retval      无
*/
static void item_hover_handler(lv_event_t *e)
{
    lv_obj_t *item = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_PRESSED) {
        lv_obj_add_style(item, &item_hover_style, LV_PART_MAIN);
    } else if (code == LV_EVENT_RELEASED || code == LV_EVENT_PRESS_LOST) {
        lv_obj_remove_style(item, &item_hover_style, LV_PART_MAIN);
    }
}

/**
@brief       删除按钮事件回调函数
@param       e: 事件数据
@retval      无
*/
static void delete_btn_handler(lv_event_t *e)
{
    // lv_obj_t *btn = lv_event_get_target(e); // btn 变量未使用
    int log_index = (int)(intptr_t)lv_event_get_user_data(e);

    // 查找要删除的日志项
    int pos = find_log_item_by_index(log_index);
    if (pos == -1) return;

    // 删除UI对象
    lv_obj_del(log_items[pos].item_obj);

    // 从数组中移除该项
    for (int i = pos; i < log_count - 1; i++) {
        log_items[i] = log_items[i + 1];
    }
    log_count--;

    printf("删除日志项，索引: %d, 剩余日志数: %d\n", log_index, log_count);
}

/**
@brief       添加一条新日志
@param       ui: UI 结构体指针
@param       text: 日志文本
@retval      无
*/
void add_log_item(lv_ui *ui, const char *text)
{
    // 如果日志数量达到上限，删除最早的日志
    if (log_count >= MAX_LOGS) {
        lv_obj_del(log_items[0].item_obj);

        // 前移所有日志项
        for (int i = 0; i < log_count - 1; i++) {
            log_items[i] = log_items[i + 1];
        }
        log_count = MAX_LOGS - 1;
    }

    // 添加新日志到数组
    log_items[log_count].index = next_index++;
    strncpy(log_items[log_count].text, text, sizeof(log_items[log_count].text) - 1);
    log_items[log_count].text[sizeof(log_items[log_count].text) - 1] = '\0';

    // 创建列表项容器
    lv_obj_t *item = lv_obj_create(log_list);
    log_items[log_count].item_obj = item;

    lv_obj_set_size(item, LV_PCT(100), 60);
    lv_obj_set_style_pad_bottom(item, 5, LV_PART_MAIN);
    lv_obj_add_style(item, &item_style, LV_PART_MAIN);

    // 添加悬停效果
    lv_obj_add_event_cb(item, item_hover_handler, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(item, item_hover_handler, LV_EVENT_RELEASED, NULL);
    lv_obj_add_event_cb(item, item_hover_handler, LV_EVENT_PRESS_LOST, NULL);

    // 添加日志文本标签
    lv_obj_t *text_label = lv_label_create(item);
    lv_label_set_text(text_label, text);
    lv_label_set_long_mode(text_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(text_label, LV_PCT(80));
    lv_obj_align(text_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_add_style(text_label, &text_style, LV_PART_MAIN);

    // 添加删除按钮
    lv_obj_t *delete_btn = lv_btn_create(item);
    lv_obj_set_size(delete_btn, 32, 32);
    lv_obj_align(delete_btn, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_style(delete_btn, &delete_btn_style, LV_PART_MAIN);
    lv_obj_add_style(delete_btn, &delete_btn_hover_style, LV_PART_MAIN | LV_STATE_PRESSED);

    // 删除按钮图标
    lv_obj_t *btn_icon = lv_label_create(delete_btn);
    lv_label_set_text(btn_icon, LV_SYMBOL_CLOSE);
    lv_obj_set_style_text_color(btn_icon, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(btn_icon, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_center(btn_icon);

    // 绑定删除事件
    lv_obj_add_event_cb(delete_btn, delete_btn_handler, LV_EVENT_CLICKED,
                         (void *)(intptr_t)log_items[log_count].index);

    log_count++;

    // 滚动到最新日志
    lv_obj_scroll_to_view(item, LV_ANIM_ON);

    printf("添加日志项，索引: %d, 当前日志数: %d\n", log_items[log_count - 1].index, log_count);
}

/**
@brief       初始化自定义日志列表
@param       ui: UI 结构体指针
@retval      无
*/
void init_custom_log_list(lv_ui *ui)
{
    // 初始化样式
    init_styles();

    // 创建日志列表
    log_list = lv_obj_create(ui->scrLog_cont_list);
    lv_obj_set_size(log_list, 680, 310);
    lv_obj_align(log_list, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_scrollbar_mode(log_list, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_set_scroll_dir(log_list, LV_DIR_VER);

    // 应用样式
    lv_obj_add_style(log_list, &list_style, LV_PART_MAIN);
    lv_obj_add_style(log_list, &scrollbar_style, LV_PART_SCROLLBAR);

    // 设置flex布局
    lv_obj_set_flex_flow(log_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(log_list, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // 初始化变量
    log_count = 0;
    next_index = 1;
      // 添加初始日志项（示例）
    add_log_item(ui, "系统启动完成 - 设备正常运行");
    add_log_item(ui, "日志：2025-1-15 13:16 - 0错位0短路0断路");
    add_log_item(ui, "日志：2025-1-15 13:17 - 0错位0短路0断路");
    add_log_item(ui, "日志：2025-1-15 13:18 - 检测到1个警告");
}

/**
@brief       获取当前日志数量
@param       无
@retval      当前日志数量
*/
int get_log_count(void)
{
    return log_count;
}