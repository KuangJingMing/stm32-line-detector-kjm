#include "main.h"

#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"
#include "custom.h"
#include "gui_guider.h"

lv_ui guider_ui;

#define UNIT_TEST 1

void unit_test(void)
{
    rtc_unit_test();
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
    btim_timx_int_init(100 - 1, 2400 - 1); // lvgl base time
    W25QXX_Init();
    RTC_Init();
    RTC_Set_WakeUp(RTC_WAKEUPCLOCK_CK_SPRE_16BITS, 0);
#if UNIT_TEST
    unit_test();
    while (1)
    {
    }
#endif
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    setup_ui(&guider_ui);

    while (1)
    {
        lv_task_handler();
        delay_ms(5);
    }
}
