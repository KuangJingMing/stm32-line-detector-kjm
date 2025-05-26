#include "./BSP/HC165/hc165.h"


// 存储所有引脚状态的内部缓冲区
static uint8_t pin_buffer[HC165_CHIP_COUNT];

/**
 * @brief 初始化74HC165控制引脚
 */
void HC165_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // 使能GPIOA时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // 配置SH/LD和CLK为输出引脚
    GPIO_InitStruct.Pin = HC165_SH_LD_PIN | HC165_CLK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // 配置QH为输入引脚
    GPIO_InitStruct.Pin = HC165_QH_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN; // 下拉电阻，根据需要调整
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(HC165_QH_PORT, &GPIO_InitStruct);
    
    // 初始化引脚状态
    HC165_SH_LD_HIGH(); // 空闲状态为高电平
    HC165_CLK_LOW();    // 时钟空闲为低电平
    
    // 清空内部缓冲区
    for (int i = 0; i < HC165_CHIP_COUNT; i++)
    {
        pin_buffer[i] = 0;
    }
}

/**
 * @brief 装载并行数据到移位寄存器
 */
void HC165_LoadData(void)
{
    HC165_SH_LD_LOW();   // 拉低SH/LD，装载并行数据
    HC165_DELAY_US(1);   // 等待数据稳定
    HC165_SH_LD_HIGH();  // 拉高SH/LD，切换到移位模式
    HC165_DELAY_US(1);   // 等待切换完成
}

/**
 * @brief 读取一位数据
 * @return 读取到的位值(0或1)
 */
uint8_t HC165_ReadBit(void)
{
    uint8_t bit_val;
    
    // 读取当前QH状态
    bit_val = (HC165_QH_READ() == GPIO_PIN_SET) ? 1 : 0;
    
    // 产生时钟脉冲，移位获取下一位
    HC165_CLK_HIGH();
    HC165_DELAY_US(1);
    HC165_CLK_LOW();
    HC165_DELAY_US(1);
    
    return bit_val;
}

/**
 * @brief 读取一个字节数据
 * @return 读取到的字节值
 */
uint8_t HC165_ReadByte(void)
{
    uint8_t data = 0;
    
    for (int i = 7; i >= 0; i--) // 从高位开始读取
    {
        if (HC165_ReadBit())
        {
            data |= (1 << i);
        }
    }
    
    return data;
}

/**
 * @brief 读取所有引脚状态到数组
 * @param pin_states: 存储引脚状态的数组，100个元素，0表示低电平，1表示高电平
 */
void HC165_ReadPins(uint8_t *pin_states)
{
    // 装载并行数据
    HC165_LoadData();
    
    // 从第一个芯片开始读取数据(因为第一个芯片的数据先输出)
    for (int chip = 0; chip < HC165_CHIP_COUNT; chip++)
    {
        pin_buffer[chip] = HC165_ReadByte();
    }
    
    // 将字节数据转换为引脚状态数组
    for (int pin = 0; pin < HC165_TOTAL_PINS; pin++)
    {
        int chip_index = pin / 8;          // 确定是第几个芯片
        int bit_index = pin % 8;           // 确定是芯片的第几位
        
        if (chip_index < HC165_CHIP_COUNT)
        {
            pin_states[pin] = (pin_buffer[chip_index] >> bit_index) & 0x01;
        }
        else
        {
            pin_states[pin] = 0; // 超出范围的引脚设为0
        }
    }
}

/**
 * @brief 读取单个引脚状态
 * @param pin_number: 引脚编号(0-99)
 * @return 引脚状态(0或1)，如果引脚编号无效返回0
 */
uint8_t HC165_ReadSinglePin(uint8_t pin_number)
{
    if (pin_number >= HC165_TOTAL_PINS)
        return 0;
    
    uint8_t pin_states[HC165_TOTAL_PINS];
    HC165_ReadPins(pin_states);
    
    return pin_states[pin_number];
}

/**
 * @brief 读取所有引脚状态（简化版本）
 * @param pin_states: 存储引脚状态的数组，100个元素
 */
void HC165_ReadAllPins(uint8_t *pin_states)
{
    HC165_ReadPins(pin_states);
}

/**
 * @brief 从引脚状态数组中获取指定引脚状态
 * @param pin_states: 引脚状态数组
 * @param pin_number: 引脚编号(0-99)
 * @return 引脚状态(0或1)
 */
uint8_t HC165_GetPinState(const uint8_t *pin_states, uint8_t pin_number)
{
    if (pin_number >= HC165_TOTAL_PINS)
        return 0;
    
    return pin_states[pin_number];
}

/**
 * @brief 检测引脚状态变化
 * @param old_states: 旧的引脚状态数组
 * @param new_states: 新的引脚状态数组  
 * @param changed_pins: 存储发生变化的引脚编号，-1表示结束
 * @param max_changes: 最大记录变化数量
 * @return 发生变化的引脚数量
 */
uint8_t HC165_DetectChanges(const uint8_t *old_states, const uint8_t *new_states, 
                           int16_t *changed_pins, uint8_t max_changes)
{
    uint8_t change_count = 0;
    
    for (int pin = 0; pin < HC165_TOTAL_PINS && change_count < max_changes; pin++)
    {
        if (old_states[pin] != new_states[pin])
        {
            changed_pins[change_count] = pin;
            change_count++;
        }
    }
    
    // 结束标记
    if (change_count < max_changes)
    {
        changed_pins[change_count] = -1;
    }
    
    return change_count;
}
