#include "./BSP/QSPI/qspi.h"
#include "stm32h7xx_hal.h" // ȷ������ HAL ��ͷ�ļ�
#include "stdio.h"

//////////////////////////////////////////////////////////////////////////////////	 
								  
////////////////////////////////////////////////////////////////////////////////// 	 

// �ȴ�״̬��־
// flag: ��Ҫ�ȴ��ı�־λ
// sta: ��Ҫ�ȴ���״̬
// wtime: �ȴ�ʱ��
// ����ֵ: 0, �ȴ��ɹ�; 1, �ȴ�ʧ��.
u8 QSPI_Wait_Flag(u32 flag, u8 sta, u32 wtime)
{
    u8 flagsta = 0;
    while (wtime)
    {
        flagsta = (QUADSPI->SR & flag) ? 1 : 0; 
        if (flagsta == sta) break;
        wtime--;
    }
    if (wtime) return 0;
    else return 1;
}

// ��ʼ�� QSPI �ӿ�
// ����ֵ: 0, �ɹ�; 1, ʧ��;
u8 QSPI_Init(void)
{
    u32 tempreg = 0;
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ʹ��ʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE(); // ʹ�� PORTB ʱ��
    __HAL_RCC_GPIOF_CLK_ENABLE(); // ʹ�� PORTF ʱ��
    __HAL_RCC_QSPI_CLK_ENABLE();  // ʹ�� QSPI ʱ��

    // ���� GPIO ���� (ʹ�� HAL ��)
    // PB2: QSPI_CLK (Alternate = GPIO_AF9_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI; // �����ֲ�ȷ�� PB2 �� QSPI CLK ������ AF9
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // PB6: QSPI_NCS (Alternate = GPIO_AF10_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI; // �����ֲ�ȷ�� PB6 �� QSPI NCS ������ AF10
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // PF8: QSPI_IO0 (Alternate = GPIO_AF10_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI; // �����ֲ�ȷ�� PF8 �� QSPI IO0 ������ AF10
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // PF9: QSPI_IO1 (Alternate = GPIO_AF10_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI; // �����ֲ�ȷ�� PF9 �� QSPI IO1 ������ AF10
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // PF7: QSPI_IO2 (Alternate = GPIO_AF9_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI; // �����ֲ�ȷ�� PF7 �� QSPI IO2 ������ AF9
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // PF6: QSPI_IO3 (Alternate = GPIO_AF9_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI; // �����ֲ�ȷ�� PF6 �� QSPI IO3 ������ AF9
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // ��λ QSPI
    __HAL_RCC_QSPI_FORCE_RESET();   // ��λ QSPI
    __HAL_RCC_QSPI_RELEASE_RESET(); // ֹͣ��λ QSPI

    if (QSPI_Wait_Flag(1 << 5, 0, 0xFFFF) == 0) // �ȴ� BUSY ����
    {
        // ����ʱ��Ƶ�ʣ��ӷ�Ƶ4��Ϊ��Ƶ8 (200M/8=25MHz)
        tempreg = (16 - 1) << 24; // ���͵�25MHz
        tempreg |= (4 - 1) << 8; // FIFO��ֵ
        tempreg |= 0 << 7;       // ѡ��FLASH1
        tempreg |= 0 << 6;       // ��ֹ˫����ģʽ
        tempreg |= 1 << 4;       // ������λ�������
        QUADSPI->CR = tempreg;
        
        tempreg = (25 - 1) << 16; // FLASH��С
        tempreg |= (8 - 1) << 8;  // ����Ƭѡ�ߵ�ƽʱ�䵽8��ʱ��
        tempreg |= 1 << 0;        // Mode3
        QUADSPI->DCR = tempreg;
        QUADSPI->CR |= 1 << 0;    // ʹ��QSPI
    }
    else
    {
        return 1;
    }
    return 0;
}

// QSPI �������� (���ຯ�����ֲ���)
// ... (QSPI_Send_CMD, QSPI_Receive, QSPI_Transmit ��������) ...
void QSPI_Send_CMD(u8 cmd, u32 addr, u8 mode, u8 dmcycle)
{
    u32 tempreg = 0;	
    u8 status;
    if (QSPI_Wait_Flag(1 << 5, 0, 0xFFFF) == 0) // �ȴ� BUSY ����
    {
        tempreg = 0 << 31;                       // ��ֹ DDR ģʽ
        tempreg |= 0 << 28;                      // ÿ�ζ�����ָ��
        tempreg |= 0 << 26;                      // ���дģʽ
        tempreg |= ((u32)mode >> 6) << 24;       // ��������ģʽ
        tempreg |= (u32)dmcycle << 18;           // ���ÿ�ָ��������
        tempreg |= ((u32)(mode >> 4) & 0x03) << 12; // ���õ�ַ����
        tempreg |= ((u32)(mode >> 2) & 0x03) << 10; // ���õ�ַģʽ
        tempreg |= ((u32)(mode >> 0) & 0x03) << 8;  // ����ָ��ģʽ
        tempreg |= cmd;                          // ����ָ��
        QUADSPI->CCR = tempreg;                  // ���� CCR �Ĵ���
        if (mode & 0x0C)                         // ��ָ��+��ַҪ����
        {
            QUADSPI->AR = addr;                  // ���õ�ַ�Ĵ���
        } 
        if ((mode & 0xC0) == 0)                  // �����ݴ��䣬�ȴ�ָ������
        {
            status = QSPI_Wait_Flag(1 << 1, 1, 0xFFFF); // �ȴ� TCF�����������
            if (status == 0)
            {
                QUADSPI->FCR |= 1 << 1;          // ��� TCF ��־λ 
            }
        }
    }	
}

u8 QSPI_Receive(u8* buf, u32 datalen)
{
    u32 tempreg = QUADSPI->CCR;
    u32 addrreg = QUADSPI->AR; 	
    u8 status;
    vu32 *data_reg = &QUADSPI->DR;
    QUADSPI->DLR = datalen - 1;                 // �������ݴ��䳤��
    tempreg &= ~(3 << 26);                      // ��� FMODE ԭ��������
    tempreg |= 1 << 26;                         // ���� FMODE Ϊ��Ӷ�ȡģʽ
    QUADSPI->FCR |= 1 << 1;                     // ��� TCF ��־λ
    QUADSPI->CCR = tempreg;                     // ��д CCR �Ĵ���
    QUADSPI->AR = addrreg;                      // ��д AR �Ĵ�������������
    while (datalen)
    {
        status = QSPI_Wait_Flag(3 << 1, 1, 0xFFFF); // �ȵ� FTF �� TCF�������յ�������
        if (status == 0)                        // �ȴ��ɹ�
        {
            *buf++ = *(vu8 *)data_reg;
            datalen--;
        }
        else break;
    }
    if (status == 0)
    {
        QUADSPI->CR |= 1 << 2;                      // ��ֹ���� 
        status = QSPI_Wait_Flag(1 << 1, 1, 0xFFFF); // �ȴ� TCF�������ݴ������
        if (status == 0)
        {
            QUADSPI->FCR |= 1 << 1;                 // ��� TCF ��־λ 
            status = QSPI_Wait_Flag(1 << 5, 0, 0xFFFF); // �ȴ� BUSY λ����
        }
    }
    return status;
} 

u8 QSPI_Transmit(u8* buf, u32 datalen)
{
    u32 tempreg = QUADSPI->CCR;
    u32 addrreg = QUADSPI->AR; 
    u8 status;
    vu32 *data_reg = &QUADSPI->DR;
    
    QUADSPI->DLR = datalen - 1;                 
    tempreg &= ~(3 << 26);                      
    tempreg |= 0 << 26;                         
    QUADSPI->FCR |= 1 << 1;                     
    QUADSPI->CCR = tempreg;                     
    
    while (datalen)
    {
        status = QSPI_Wait_Flag(1 << 2, 1, 0xFFFF); // �ȴ�FTF
        if (status != 0)                        
        {
            printf("QSPI transmit timeout at byte %lu\r\n", datalen);
            break;
        }
        *(vu8 *)data_reg = *buf++;
        datalen--;
        
        // ÿ16�ֽ����С��ʱ��ȷ�����ݴ����ȶ�
        if((datalen & 0x0F) == 0) {
            for(volatile int i = 0; i < 100; i++);
        }
    }
    
    if (status == 0)
    {
        QUADSPI->CR |= 1 << 2;                      
        status = QSPI_Wait_Flag(1 << 1, 1, 0xFFFF); 
        if (status == 0)
        {
            QUADSPI->FCR |= 1 << 1;                 
            status = QSPI_Wait_Flag(1 << 5, 0, 0xFFFF); 
        }
    }
    return status;
}

