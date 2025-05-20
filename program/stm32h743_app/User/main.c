#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/SDRAM/sdram.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/MPU/mpu.h"
#include "./BSP/TIMER/btim.h"

/* LVGL */
#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"

/**
 * @brief 按钮点击事件的回调函数
 * @param event 事件数据
 */
static void button_event_handler(lv_event_t *event)
{
    lv_obj_t *btn = lv_event_get_target(event);  // 获取触发事件的按钮对象
    lv_obj_t *label = lv_obj_get_child(btn, 0); // 获取按钮上的标签（假设标签是按钮的子对象）
    
    // 切换标签文本，模拟点击响应
    const char *current_text = lv_label_get_text(label);
    if (strcmp(current_text, "Click Me!") == 0) {
        lv_label_set_text(label, "Clicked!");
    } else {
        lv_label_set_text(label, "Click Me!");
    }
}

/**
 * @brief 初始化 LVGL UI
 */
static void ui_init(void)
{
    // 创建一个容器，用于放置 UI 元素
    lv_obj_t *container = lv_obj_create(lv_scr_act()); // lv_scr_act() 返回当前活动屏幕
    lv_obj_set_size(container, LV_PCT(100), LV_PCT(100)); // 容器大小设置为屏幕的 100%
    lv_obj_set_style_bg_color(container, lv_color_hex(0xFFFFFF), 0); // 设置背景色为白色
    
    // 创建一个标签，显示欢迎消息
    lv_obj_t *label_welcome = lv_label_create(container);
    lv_label_set_text(label_welcome, "Welcome to LVGL!");
    lv_obj_set_pos(label_welcome, 50, 50); // 设置标签位置
    lv_obj_set_style_text_color(label_welcome, lv_color_hex(0x0000FF), 0); // 设置文本颜色为蓝色
    lv_obj_set_style_text_font(label_welcome, &lv_font_montserrat_16, 0); // 设置字体
    
    // 创建一个按钮
    lv_obj_t *button = lv_btn_create(container);
    lv_obj_set_size(button, 120, 50); // 设置按钮大小
    lv_obj_set_pos(button, 50, 100); // 设置按钮位置
    lv_obj_set_style_bg_color(button, lv_color_hex(0x00FF00), 0); // 设置按钮背景色为绿色
    
    // 在按钮上添加一个标签
    lv_obj_t *button_label = lv_label_create(button);
    lv_label_set_text(button_label, "Click Me!");
    lv_obj_center(button_label); // 将标签居中显示在按钮上
    
    // 注册按钮点击事件回调
    lv_obj_add_event_cb(button, button_event_handler, LV_EVENT_CLICKED, NULL);
}

int main(void)
{
    sys_cache_enable();                  // 打开 L1-Cache
    HAL_Init();                          // 初始化 HAL 库
    sys_stm32_clock_init(192, 5, 2, 4);  // 设置时钟, 480MHz
    delay_init(480);                     // 延时初始化
    usart_init(115200);                  // 串口初始化
    mpu_memory_protection();             // 保护相关存储区域
    led_init();                          // 初始化 LED
    key_init();                          // 初始化 KEY
    sdram_init();                        // 初始化 SDRAM
    btim_timx_int_init(100-1, 2400-1);   // 初始化定时器

    lv_init();                           // LVGL 系统初始化
    lv_port_disp_init();                 // LVGL 显示接口初始化，放在 lv_init() 的后面
    lv_port_indev_init();                // LVGL 输入接口初始化，放在 lv_init() 的后面
    
    ui_init();                           // 初始化 UI 界面

    while (1)
    {
        lv_task_handler();               // 处理 LVGL 任务
        delay_ms(5);                     // 每 5ms 调用一次，确保界面刷新
    }
}
