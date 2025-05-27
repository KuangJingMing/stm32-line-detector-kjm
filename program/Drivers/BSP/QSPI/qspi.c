#include "./BSP/QSPI/qspi.h"
#include "stm32h7xx_hal.h" // 确保包含 HAL 库头文件
#include "stdio.h"

//////////////////////////////////////////////////////////////////////////////////	 
								  
////////////////////////////////////////////////////////////////////////////////// 	 

// 等待状态标志
// flag: 需要等待的标志位
// sta: 需要等待的状态
// wtime: 等待时间
// 返回值: 0, 等待成功; 1, 等待失败.
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

// 初始化 QSPI 接口
// 返回值: 0, 成功; 1, 失败;
u8 QSPI_Init(void)
{
    u32 tempreg = 0;
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能时钟
    __HAL_RCC_GPIOB_CLK_ENABLE(); // 使能 PORTB 时钟
    __HAL_RCC_GPIOF_CLK_ENABLE(); // 使能 PORTF 时钟
    __HAL_RCC_QSPI_CLK_ENABLE();  // 使能 QSPI 时钟

    // 配置 GPIO 引脚 (使用 HAL 库)
    // PB2: QSPI_CLK (Alternate = GPIO_AF9_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI; // 根据手册确认 PB2 的 QSPI CLK 功能是 AF9
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // PB6: QSPI_NCS (Alternate = GPIO_AF10_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI; // 根据手册确认 PB6 的 QSPI NCS 功能是 AF10
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // PF8: QSPI_IO0 (Alternate = GPIO_AF10_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI; // 根据手册确认 PF8 的 QSPI IO0 功能是 AF10
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // PF9: QSPI_IO1 (Alternate = GPIO_AF10_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI; // 根据手册确认 PF9 的 QSPI IO1 功能是 AF10
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // PF7: QSPI_IO2 (Alternate = GPIO_AF9_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI; // 根据手册确认 PF7 的 QSPI IO2 功能是 AF9
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // PF6: QSPI_IO3 (Alternate = GPIO_AF9_QUADSPI)
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI; // 根据手册确认 PF6 的 QSPI IO3 功能是 AF9
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // 复位 QSPI
    __HAL_RCC_QSPI_FORCE_RESET();   // 复位 QSPI
    __HAL_RCC_QSPI_RELEASE_RESET(); // 停止复位 QSPI

    if (QSPI_Wait_Flag(1 << 5, 0, 0xFFFF) == 0) // 等待 BUSY 空闲
    {
        // 降低时钟频率：从分频4改为分频8 (200M/8=25MHz)
        tempreg = (16 - 1) << 24; // 降低到25MHz
        tempreg |= (4 - 1) << 8; // FIFO阈值
        tempreg |= 0 << 7;       // 选择FLASH1
        tempreg |= 0 << 6;       // 禁止双闪存模式
        tempreg |= 1 << 4;       // 采样移位半个周期
        QUADSPI->CR = tempreg;
        
        tempreg = (25 - 1) << 16; // FLASH大小
        tempreg |= (8 - 1) << 8;  // 增加片选高电平时间到8个时钟
        tempreg |= 1 << 0;        // Mode3
        QUADSPI->DCR = tempreg;
        QUADSPI->CR |= 1 << 0;    // 使能QSPI
    }
    else
    {
        return 1;
    }
    return 0;
}

// QSPI 发送命令 (其余函数保持不变)
// ... (QSPI_Send_CMD, QSPI_Receive, QSPI_Transmit 函数代码) ...
void QSPI_Send_CMD(u8 cmd, u32 addr, u8 mode, u8 dmcycle)
{
    u32 tempreg = 0;	
    u8 status;
    if (QSPI_Wait_Flag(1 << 5, 0, 0xFFFF) == 0) // 等待 BUSY 空闲
    {
        tempreg = 0 << 31;                       // 禁止 DDR 模式
        tempreg |= 0 << 28;                      // 每次都发送指令
        tempreg |= 0 << 26;                      // 间接写模式
        tempreg |= ((u32)mode >> 6) << 24;       // 设置数据模式
        tempreg |= (u32)dmcycle << 18;           // 设置空指令周期数
        tempreg |= ((u32)(mode >> 4) & 0x03) << 12; // 设置地址长度
        tempreg |= ((u32)(mode >> 2) & 0x03) << 10; // 设置地址模式
        tempreg |= ((u32)(mode >> 0) & 0x03) << 8;  // 设置指令模式
        tempreg |= cmd;                          // 设置指令
        QUADSPI->CCR = tempreg;                  // 设置 CCR 寄存器
        if (mode & 0x0C)                         // 有指令+地址要发送
        {
            QUADSPI->AR = addr;                  // 设置地址寄存器
        } 
        if ((mode & 0xC0) == 0)                  // 无数据传输，等待指令发送完成
        {
            status = QSPI_Wait_Flag(1 << 1, 1, 0xFFFF); // 等待 TCF，即传输完成
            if (status == 0)
            {
                QUADSPI->FCR |= 1 << 1;          // 清除 TCF 标志位 
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
    QUADSPI->DLR = datalen - 1;                 // 设置数据传输长度
    tempreg &= ~(3 << 26);                      // 清除 FMODE 原来的设置
    tempreg |= 1 << 26;                         // 设置 FMODE 为间接读取模式
    QUADSPI->FCR |= 1 << 1;                     // 清除 TCF 标志位
    QUADSPI->CCR = tempreg;                     // 回写 CCR 寄存器
    QUADSPI->AR = addrreg;                      // 回写 AR 寄存器，触发传输
    while (datalen)
    {
        status = QSPI_Wait_Flag(3 << 1, 1, 0xFFFF); // 等到 FTF 和 TCF，即接收到了数据
        if (status == 0)                        // 等待成功
        {
            *buf++ = *(vu8 *)data_reg;
            datalen--;
        }
        else break;
    }
    if (status == 0)
    {
        QUADSPI->CR |= 1 << 2;                      // 终止传输 
        status = QSPI_Wait_Flag(1 << 1, 1, 0xFFFF); // 等待 TCF，即数据传输完成
        if (status == 0)
        {
            QUADSPI->FCR |= 1 << 1;                 // 清除 TCF 标志位 
            status = QSPI_Wait_Flag(1 << 5, 0, 0xFFFF); // 等待 BUSY 位清零
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
        status = QSPI_Wait_Flag(1 << 2, 1, 0xFFFF); // 等待FTF
        if (status != 0)                        
        {
            printf("QSPI transmit timeout at byte %lu\r\n", datalen);
            break;
        }
        *(vu8 *)data_reg = *buf++;
        datalen--;
        
        // 每16字节添加小延时，确保数据传输稳定
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

