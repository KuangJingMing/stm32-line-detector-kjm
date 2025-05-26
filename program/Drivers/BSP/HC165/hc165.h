#ifndef __HC165_CONTROL_H
#define __HC165_CONTROL_H

#include "stm32h7xx_hal.h"
#include <stdint.h>

// 74HC165控制引脚定义
#define HC165_SH_LD_PORT   GPIOA
#define HC165_SH_LD_PIN    GPIO_PIN_1

#define HC165_CLK_PORT     GPIOA
#define HC165_CLK_PIN      GPIO_PIN_2

#define HC165_QH_PORT      GPIOA
#define HC165_QH_PIN       GPIO_PIN_3

// 74HC165级联数量和总引脚数
#define HC165_CHIP_COUNT   13    // 100pins需要13个74HC165芯片
#define HC165_TOTAL_PINS   100

// 引脚操作宏定义
#define HC165_SH_LD_HIGH() HAL_GPIO_WritePin(HC165_SH_LD_PORT, HC165_SH_LD_PIN, GPIO_PIN_SET)
#define HC165_SH_LD_LOW()  HAL_GPIO_WritePin(HC165_SH_LD_PORT, HC165_SH_LD_PIN, GPIO_PIN_RESET)

#define HC165_CLK_HIGH()   HAL_GPIO_WritePin(HC165_CLK_PORT, HC165_CLK_PIN, GPIO_PIN_SET)
#define HC165_CLK_LOW()    HAL_GPIO_WritePin(HC165_CLK_PORT, HC165_CLK_PIN, GPIO_PIN_RESET)

#define HC165_QH_READ()    HAL_GPIO_ReadPin(HC165_QH_PORT, HC165_QH_PIN)

// 延时宏定义（根据需要调整）
#define HC165_DELAY_US(us)  do { \
    for(volatile uint32_t i = 0; i < (us * 100); i++) { \
        __NOP(); \
    } \
} while(0)

// 函数声明
void HC165_Init(void);
uint8_t HC165_ReadBit(void);
uint8_t HC165_ReadByte(void);
void HC165_LoadData(void);
void HC165_ReadPins(uint8_t *pin_states);
uint8_t HC165_ReadSinglePin(uint8_t pin_number);
void HC165_ReadAllPins(uint8_t *pin_states);
uint8_t HC165_GetPinState(const uint8_t *pin_states, uint8_t pin_number);

#endif /* __HC165_CONTROL_H */
