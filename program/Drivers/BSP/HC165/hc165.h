#ifndef __74HC165_H
#define __74HC165_H

#include "stm32h7xx_hal.h"
#include <stdint.h>

// 引脚定义
#define HC165_SH_LD_PIN    GPIO_PIN_1
#define HC165_SH_LD_PORT   GPIOA
#define HC165_CLK_PIN      GPIO_PIN_2
#define HC165_CLK_PORT     GPIOA
#define HC165_QH_PIN       GPIO_PIN_3
#define HC165_QH_PORT      GPIOA

// 总引脚数量
#define HC165_TOTAL_PINS   100
// 需要的芯片数量 (每个74HC165有8个输入)
#define HC165_CHIP_COUNT   ((HC165_TOTAL_PINS + 7) / 8)

// 函数声明
void HC165_Init(void);
uint8_t HC165_ReadPins(uint8_t *pin_states);
uint8_t HC165_ReadSinglePin(uint8_t pin_number);

#endif
