#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/MPU/mpu.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/SDRAM/sdram.h"
#include "./USMART/usmart.h"
#include "./BSP/TOUCH/touch.h"
#include "./BSP/TIMER/timer.h"

#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"



/* ȫ�ֱ��� */
lv_obj_t *label_hello;      // ��ʾ���ֱ�ǩ
lv_obj_t *btn;              // ��ť
lv_obj_t *label_btn;        // ��ť����
lv_obj_t *led_indicator;    // LEDָʾ��
lv_obj_t *slider;           // ������
lv_obj_t *label_slider;     // ��������ֵ��ʾ

/* ��ť����¼��ص����� */
static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    
    if(code == LV_EVENT_CLICKED) {
        printf("Button clicked!\r\n");
        
        /* �л�LED״̬ */
        static bool led_state = false;
        led_state = !led_state;
        
        if(led_state) {
            LED0(0);  // ����LED
            lv_led_on(led_indicator);
            lv_label_set_text(label_btn, "LED ON");
        } else {
            LED0(1);  // �ر�LED
            lv_led_off(led_indicator);
            lv_label_set_text(label_btn, "LED OFF");
        }
    }
}

/* �������¼��ص����� */
static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    
    /* ������ֵ��ʾ */
    lv_label_set_text_fmt(label_slider, "Value: %d", (int)value);
    
    printf("Slider value: %d\r\n", (int)value);
}

/* ����UI���� */
void create_demo_ui(void)
{
    /* 1. ���������ǩ */
    label_hello = lv_label_create(lv_scr_act());
    lv_label_set_text(label_hello, "STM32H7 + LVGL Demo");
    lv_obj_set_style_text_font(label_hello, &lv_font_montserrat_20, 0);
    lv_obj_align(label_hello, LV_ALIGN_TOP_MID, 0, 20);
    
    /* 2. ������ť */
    btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, 120, 50);
    lv_obj_align(btn, LV_ALIGN_CENTER, -80, -50);
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);
    
    /* ��ť���� */
    label_btn = lv_label_create(btn);
    lv_label_set_text(label_btn, "LED OFF");
    lv_obj_center(label_btn);
    
    /* 3. ����LEDָʾ�� */
    led_indicator = lv_led_create(lv_scr_act());
    lv_obj_set_size(led_indicator, 40, 40);
    lv_obj_align(led_indicator, LV_ALIGN_CENTER, 80, -50);
    lv_led_set_color(led_indicator, lv_color_hex(0xFF0000));  // ��ɫLED
    lv_led_off(led_indicator);
    
    /* 4. ���������� */
    slider = lv_slider_create(lv_scr_act());
    lv_obj_set_width(slider, 200);
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 20);
    lv_slider_set_range(slider, 0, 100);
    lv_slider_set_value(slider, 50, LV_ANIM_OFF);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    
    /* ��������ֵ��ʾ */
    label_slider = lv_label_create(lv_scr_act());
    lv_label_set_text(label_slider, "Value: 50");
    lv_obj_align(label_slider, LV_ALIGN_CENTER, 0, 60);
    
    /* 5. ����һ���򵥵Ľ����� */
    lv_obj_t *bar = lv_bar_create(lv_scr_act());
    lv_obj_set_size(bar, 200, 20);
    lv_obj_align(bar, LV_ALIGN_CENTER, 0, 100);
    lv_bar_set_value(bar, 70, LV_ANIM_OFF);
    
    /* ��������ǩ */
    lv_obj_t *label_bar = lv_label_create(lv_scr_act());
    lv_label_set_text(label_bar, "Progress: 70%");
    lv_obj_align(label_bar, LV_ALIGN_CENTER, 0, 130);
    
    printf("UI created successfully!\r\n");
}


int main(void)
{
		sys_cache_enable();
		HAL_Init();    
    sys_stm32_clock_init(160, 5, 2, 4);     /* ����ʱ��, 400Mhz */
    delay_init(400);                        /* ��ʱ��ʼ�� */
    usart_init(100, 115200);                /* ��ʼ��USART */
    led_init();                             /* ��ʼ��LED */
    mpu_memory_protection();                /* ������ش洢���� */
    sdram_init();                           /* ��ʼ��SDRAM */
		btim_timx_int_init(100-1,2400-1);  
	
    lv_init();                              /* lvglϵͳ��ʼ�� */
    lv_port_disp_init();                    /* lvgl��ʾ�ӿڳ�ʼ�� */
    lv_port_indev_init();                   /* lvgl����ӿڳ�ʼ�� */
    
    /* ������ʾUI */
    create_demo_ui();
    
    while (1) {
        lv_task_handler();
        delay_ms(10);
    }
}

