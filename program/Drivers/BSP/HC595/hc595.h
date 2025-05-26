#ifndef __HC595_CONTROL_H
#define __HC595_CONTROL_H

#include "stm32h7xx_hal.h"
#include <stdint.h>

// 74HC595控制引脚定义
#define HC595_STCP_PORT    GPIOC
#define HC595_STCP_PIN     GPIO_PIN_6

#define HC595_SHCP_PORT    GPIOC
#define HC595_SHCP_PIN     GPIO_PIN_5

#define HC595_DS_PORT      GPIOC
#define HC595_DS_PIN       GPIO_PIN_4

// 74HC595级联数量和总引脚数
#define HC595_CHIP_COUNT   13    // 100pins需要13个74HC595芯片
#define HC595_TOTAL_PINS   100

// 引脚操作宏定义
#define HC595_STCP_HIGH()  HAL_GPIO_WritePin(HC595_STCP_PORT, HC595_STCP_PIN, GPIO_PIN_SET)
#define HC595_STCP_LOW()   HAL_GPIO_WritePin(HC595_STCP_PORT, HC595_STCP_PIN, GPIO_PIN_RESET)

#define HC595_SHCP_HIGH()  HAL_GPIO_WritePin(HC595_SHCP_PORT, HC595_SHCP_PIN, GPIO_PIN_SET)
#define HC595_SHCP_LOW()   HAL_GPIO_WritePin(HC595_SHCP_PORT, HC595_SHCP_PIN, GPIO_PIN_RESET)

#define HC595_DS_HIGH()    HAL_GPIO_WritePin(HC595_DS_PORT, HC595_DS_PIN, GPIO_PIN_SET)
#define HC595_DS_LOW()     HAL_GPIO_WritePin(HC595_DS_PORT, HC595_DS_PIN, GPIO_PIN_RESET)

// 函数声明
void HC595_Init(void);
void HC595_SendBit(uint8_t bit);
void HC595_SendByte(uint8_t data);
void HC595_Latch(void);
void HC595_SetPins(const uint8_t *pin_states);
void HC595_SetSinglePin(uint8_t pin_number, uint8_t state);
void HC595_SetAllPins(uint8_t state);
void HC595_ClearAllPins(void);

#endif /* __HC595_CONTROL_H */
