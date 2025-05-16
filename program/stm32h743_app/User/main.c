

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
#include "lv_demo_music.h"


int main(void)
{
    sys_cache_enable();                                         /* 打开L1-Cache */
    HAL_Init();                                                 /* 初始化HAL库 */
    sys_stm32_clock_init(192, 5, 2, 4);                         /* 设置时钟, 480Mhz */
    delay_init(480);                                            /* 延时初始化 */
    usart_init(115200);                                         /* 串口初始化 */
    mpu_memory_protection();                                    /* 保护相关存储区域 */
    led_init();                                                 /* 初始化LED */
    key_init();                                                 /* 初始化KEY */
    sdram_init();                                               /* 初始化SDRAM */
    btim_timx_int_init(100-1,2400-1);                           /* 初始化定时器 */

    lv_init();                                                  /* lvgl系统初始化 */
    lv_port_disp_init();                                        /* lvgl显示接口初始化,放在lv_init()的后面 */
    lv_port_indev_init();                                       /* lvgl输入接口初始化,放在lv_init()的后面 */
    
    lv_demo_music();                                            /* 官方例程 */
    
    while (1)
    {
        lv_task_handler();
        delay_ms(5);
    }
}


