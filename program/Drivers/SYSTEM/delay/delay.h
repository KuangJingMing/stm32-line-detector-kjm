#ifndef __DELAY_H
#define __DELAY_H

#include "stm32h7xx_hal.h"
#include <stdint.h>

void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
uint32_t delay_get_sysclk_mhz(void);

#endif
