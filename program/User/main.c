#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/MPU/mpu.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/SDRAM/sdram.h"
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
    sys_stm32_clock_init(160, 5, 2, 4); 
    delay_init(400);                     
    usart_init(100, 115200);            
    led_init();                       
    mpu_memory_protection();          
    sdram_init();               
		btim_timx_int_init(100-1,2400-1);  

    lv_init();                    
    lv_port_disp_init();         
    lv_port_indev_init();          
    
		setup_ui(&guider_ui);
    
    while (1) {
        lv_task_handler();
        delay_ms(5);
    }
}

