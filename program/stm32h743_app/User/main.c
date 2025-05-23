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
#include "custom.h"
#include "gui_guider.h"

lv_ui guider_ui;


int main(void)
{
		sys_cache_enable();
		HAL_Init();    
    sys_stm32_clock_init(160, 5, 2, 4);     /* 设置时钟, 400Mhz */
    delay_init(400);                        /* 延时初始化 */
    usart_init(100, 115200);                /* 初始化USART */
    led_init();                             /* 初始化LED */
    mpu_memory_protection();                /* 保护相关存储区域 */
    sdram_init();                           /* 初始化SDRAM */
		btim_timx_int_init(100-1,2400-1);  
	
    lv_init();                              /* lvgl系统初始化 */
    lv_port_disp_init();                    /* lvgl显示接口初始化 */
    lv_port_indev_init();                   /* lvgl输入接口初始化 */
    
		setup_ui(&guider_ui);
    
    while (1) {
        lv_task_handler();
        delay_ms(10);
    }
}

