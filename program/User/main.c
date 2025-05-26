#include "main.h"

#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"
#include "custom.h"
#include "gui_guider.h"

lv_ui guider_ui;


void unit_test(void) {
	rg_test();
}

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
		btim_timx_int_init(100-1,2400-1);  //lvgl base time

		unit_test();
	
		while (1) {
		
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

