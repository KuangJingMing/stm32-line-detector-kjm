

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
    sys_cache_enable();                                         /* ��L1-Cache */
    HAL_Init();                                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(192, 5, 2, 4);                         /* ����ʱ��, 480Mhz */
    delay_init(480);                                            /* ��ʱ��ʼ�� */
    usart_init(115200);                                         /* ���ڳ�ʼ�� */
    mpu_memory_protection();                                    /* ������ش洢���� */
    led_init();                                                 /* ��ʼ��LED */
    key_init();                                                 /* ��ʼ��KEY */
    sdram_init();                                               /* ��ʼ��SDRAM */
    btim_timx_int_init(100-1,2400-1);                           /* ��ʼ����ʱ�� */

    lv_init();                                                  /* lvglϵͳ��ʼ�� */
    lv_port_disp_init();                                        /* lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ��� */
    lv_port_indev_init();                                       /* lvgl����ӿڳ�ʼ��,����lv_init()�ĺ��� */
    
    lv_demo_music();                                            /* �ٷ����� */
    
    while (1)
    {
        lv_task_handler();
        delay_ms(5);
    }
}


