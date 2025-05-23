

#ifndef __MPU_H
#define __MPU_H

#include "./SYSTEM/sys/sys.h"


/* MPU����ϸ���ù�ϵ���뿴����STM32H7����ֲ�.pdf��
 * ����ĵ���6.6��,Table 91.
 * MPU��������������Զ��壨������stm32h7xx_hal_cortex.h��
 * ����MPU->RASR�Ĵ���AP[26:24]λ������ֵ
 */ 

#include "stm32h7xx_hal.h"


static uint8_t mpu_convert_bytes_to_pot(uint32_t nbytes);   /* ��nbytesת��Ϊ2Ϊ�ڵ�ָ�� */

void mpu_disable(void); /* ��ֹMPU */
void mpu_enable(void);  /* ʹ��MPU */
void mpu_memory_protection(void);   /* MPU���� */
uint8_t mpu_set_protection(uint32_t baseaddr, uint32_t size, uint32_t rnum, uint8_t de, uint8_t ap, uint8_t sen, uint8_t cen, uint8_t ben);

#endif

















