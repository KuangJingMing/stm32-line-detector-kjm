

#ifndef __MPU_H
#define __MPU_H

#include "./SYSTEM/sys/sys.h"


/* MPU的详细设置关系，请看：《STM32H7编程手册.pdf》
 * 这个文档的6.6节,Table 91.
 * MPU保护区域许可属性定义（拷贝自stm32h7xx_hal_cortex.h）
 * 定义MPU->RASR寄存器AP[26:24]位的设置值
 */ 

#include "stm32h7xx_hal.h"


static uint8_t mpu_convert_bytes_to_pot(uint32_t nbytes);   /* 将nbytes转换为2为第的指数 */

void mpu_disable(void); /* 禁止MPU */
void mpu_enable(void);  /* 使能MPU */
void mpu_memory_protection(void);   /* MPU保护 */
uint8_t mpu_set_protection(uint32_t baseaddr, uint32_t size, uint32_t rnum, uint8_t de, uint8_t ap, uint8_t sen, uint8_t cen, uint8_t ben);

#endif

















