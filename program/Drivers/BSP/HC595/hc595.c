#include "./BSP/HC595/hc595.h"


// 存储所有引脚状态的缓冲区
static uint8_t pin_buffer[HC595_CHIP_COUNT];
/**
 * @brief 初始化74HC595控制引脚
 */
void HC595_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // 使能GPIOC时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    // 配置HC595控制引脚
    GPIO_InitStruct.Pin = HC595_STCP_PIN | HC595_SHCP_PIN | HC595_DS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    // 初始化引脚状态为低电平
    HC595_STCP_LOW();
    HC595_SHCP_LOW();
    HC595_DS_LOW();
    
    // 清空所有引脚
    HC595_ClearAllPins();
}
/**
 * @brief 发送一个位到74HC595
 * @param bit: 要发送的位(0或1)
 */
void HC595_SendBit(uint8_t bit)
{
    // 设置数据线状态
    if (bit)
        HC595_DS_HIGH();
    else
        HC595_DS_LOW();
    
    // 产生时钟脉冲
    HC595_SHCP_HIGH();
    __NOP(); // 短暂延时
    HC595_SHCP_LOW();
}
/**
 * @brief 发送一个字节到74HC595
 * @param data: 要发送的字节数据
 */
void HC595_SendByte(uint8_t data)
{
    for (int i = 7; i >= 0; i--) // 从高位开始发送
    {
        HC595_SendBit((data >> i) & 0x01);
    }
}
/**
 * @brief 锁存数据到输出端
 */
void HC595_Latch(void)
{
    HC595_STCP_HIGH();
    __NOP(); // 短暂延时
    HC595_STCP_LOW();
}
/**
 * @brief 根据数组设置引脚状态
 * @param pin_states: 引脚状态数组，100个元素，0表示低电平，非0表示高电平
 */
void HC595_SetPins(const uint8_t *pin_states)
{
    // 清空缓冲区
    for (int i = 0; i < HC595_CHIP_COUNT; i++)
    {
        pin_buffer[i] = 0;
    }
    
    // 将引脚状态转换为字节数据
    for (int pin = 0; pin < HC595_TOTAL_PINS; pin++)
    {
        if (pin_states[pin])
        {
            int chip_index = pin / 8;          // 确定是第几个芯片
            int bit_index = pin % 8;           // 确定是芯片的第几位
            pin_buffer[chip_index] |= (1 << bit_index);
        }
    }
    
    // 从最后一个芯片开始发送数据(因为是串联的)
    for (int chip = HC595_CHIP_COUNT - 1; chip >= 0; chip--)
    {
        HC595_SendByte(pin_buffer[chip]);
    }
    
    // 锁存数据
    HC595_Latch();
}
/**
 * @brief 设置单个引脚状态
 * @param pin_number: 引脚编号(0-99)
 * @param state: 引脚状态(0或1)
 */
void HC595_SetSinglePin(uint8_t pin_number, uint8_t state)
{
    if (pin_number >= HC595_TOTAL_PINS)
        return;
    
    int chip_index = pin_number / 8;
    int bit_index = pin_number % 8;
    
    if (state)
        pin_buffer[chip_index] |= (1 << bit_index);   // 置位
    else
        pin_buffer[chip_index] &= ~(1 << bit_index);  // 清位
    
    // 重新发送所有数据
    for (int chip = HC595_CHIP_COUNT - 1; chip >= 0; chip--)
    {
        HC595_SendByte(pin_buffer[chip]);
    }
    
    HC595_Latch();
}
/**
 * @brief 设置所有引脚为相同状态
 * @param state: 引脚状态(0或1)
 */
void HC595_SetAllPins(uint8_t state)
{
    uint8_t data = state ? 0xFF : 0x00;
    
    // 更新缓冲区
    for (int i = 0; i < HC595_CHIP_COUNT; i++)
    {
        pin_buffer[i] = data;
    }
    
    // 发送数据
    for (int chip = 0; chip < HC595_CHIP_COUNT; chip++)
    {
        HC595_SendByte(data);
    }
    
    HC595_Latch();
}
/**
 * @brief 清空所有引脚
 */
void HC595_ClearAllPins(void)
{
    HC595_SetAllPins(0);
}