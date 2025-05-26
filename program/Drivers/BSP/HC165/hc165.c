#include "./BSP/HC165/hc165.h"
#include "./SYSTEM/delay/delay.h"

// 精确延时函数
static void HC165_Delay_us(uint32_t us)
{
    delay_us(us);
}

void HC165_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // SH_LD引脚配置
    GPIO_InitStruct.Pin = HC165_SH_LD_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(HC165_SH_LD_PORT, &GPIO_InitStruct);
    
    // CLK引脚配置
    GPIO_InitStruct.Pin = HC165_CLK_PIN;
    HAL_GPIO_Init(HC165_CLK_PORT, &GPIO_InitStruct);
    
    // QH引脚配置
    GPIO_InitStruct.Pin = HC165_QH_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(HC165_QH_PORT, &GPIO_InitStruct);
    
    // 初始化引脚状态
    HAL_GPIO_WritePin(HC165_SH_LD_PORT, HC165_SH_LD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(HC165_CLK_PORT, HC165_CLK_PIN, GPIO_PIN_RESET);
}

uint8_t HC165_ReadPins(uint8_t *pin_states)
{
    if(pin_states == NULL)
    {
        return 0;
    }
    
    uint8_t i;
    uint8_t bit_value;
    uint8_t temp_buffer[104];
    
    // 锁存输入数据
    HAL_GPIO_WritePin(HC165_SH_LD_PORT, HC165_SH_LD_PIN, GPIO_PIN_RESET);
    HC165_Delay_us(1);
    HAL_GPIO_WritePin(HC165_SH_LD_PORT, HC165_SH_LD_PIN, GPIO_PIN_SET);
    
    // 读取第一位数据
    bit_value = HAL_GPIO_ReadPin(HC165_QH_PORT, HC165_QH_PIN);
    temp_buffer[0] = (bit_value == GPIO_PIN_SET) ? 1 : 0;
    
    // 串行读取剩余103位数据
    for(i = 1; i < 104; i++)
    {
        HAL_GPIO_WritePin(HC165_CLK_PORT, HC165_CLK_PIN, GPIO_PIN_SET);
        HC165_Delay_us(1);
        HAL_GPIO_WritePin(HC165_CLK_PORT, HC165_CLK_PIN, GPIO_PIN_RESET);
        HC165_Delay_us(1);
        
        bit_value = HAL_GPIO_ReadPin(HC165_QH_PORT, HC165_QH_PIN);
        temp_buffer[i] = (bit_value == GPIO_PIN_SET) ? 1 : 0;
    }
    
    // 数据重新排序
    for(i = 0; i < 100; i++)
    {
        pin_states[i] = temp_buffer[103 - i];
    }
    
    return 1;
}
