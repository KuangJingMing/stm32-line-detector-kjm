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
#include "./BSP/HC165/hc165.h"
#include "./BSP/HC595/hc595.h"

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
		SystemClock_Config();
		delay_init();
    usart_init(100, 115200);            
    led_init();                       
    mpu_memory_protection();          
    sdram_init();               
		btim_timx_int_init(100-1,2400-1);  

//		HC595_Init();
//		uint8_t pin_states[100] = {0};
//		for (int i = 0; i < 100; i++) {
//			HC595_SetSinglePin(i, pin_states[i]);
//		}
//		HC595_SetSinglePin(99, 1);
		while (1) {
			delay_ms(1000);
		}
    lv_init();                    
    lv_port_disp_init();         
    lv_port_indev_init();          
    
		setup_ui(&guider_ui);
    
    while (1) {
        lv_task_handler();
        delay_ms(5);
    }
}

