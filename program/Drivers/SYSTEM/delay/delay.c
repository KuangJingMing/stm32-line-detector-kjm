#include "./SYSTEM/delay/delay.h"
#include "stm32h7xx_hal.h"

static TIM_HandleTypeDef htim3;
static uint32_t g_us_tick_overflow = 0;  // 溢出计数

/**
 * @brief     TIM3初始化为微秒计数器
 */
static void TIM3_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    
    // 使能TIM3时钟
    __HAL_RCC_TIM3_CLK_ENABLE();
    
    // 获取TIM3的时钟频率
    uint32_t tim_clk = HAL_RCC_GetPCLK1Freq();
    
    // 检查APB1预分频
    RCC_ClkInitTypeDef clk_init;
    uint32_t flash_latency;
    HAL_RCC_GetClockConfig(&clk_init, &flash_latency);
    
    if (clk_init.APB1CLKDivider != RCC_HCLK_DIV1)
    {
        tim_clk *= 2;
    }
    
    // TIM3是16位定时器，配置为1MHz计数频率
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = (tim_clk / 1000000) - 1;  // 预分频到1MHz
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 0xFFFF;  // 16位最大值，不是32位！
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {

    }
    
    // 配置时钟源
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
    {

    }
    
    // 启动定时器
    if (HAL_TIM_Base_Start(&htim3) != HAL_OK)
    {

    }
}

/**
 * @brief     初始化延迟函数
 * @param     无
 * @retval    无
 */
void delay_init(void)
{
    // 初始化TIM3
    TIM3_Init();
}

/**
 * @brief     获取当前微秒计数值
 */
static uint32_t get_us_tick(void)
{
    return __HAL_TIM_GET_COUNTER(&htim3);
}

/**
 * @brief     精确微秒延时（修正版）
 */
void delay_us(uint32_t nus)
{
    uint32_t start_tick, current_tick, elapsed_us;
    
    if (nus == 0) return;
    
    // 对于长延时，分段处理
    if (nus > 60000)  // 超过60ms用HAL_Delay
    {
        HAL_Delay(nus / 1000);
        nus = nus % 1000;
        if (nus == 0) return;
    }
    
    start_tick = get_us_tick();
    
    do {
        current_tick = get_us_tick();
        
        // 处理16位计数器溢出
        if (current_tick >= start_tick)
        {
            elapsed_us = current_tick - start_tick;
        }
        else
        {
            // 16位计数器溢出
            elapsed_us = (0xFFFF - start_tick) + current_tick + 1;
        }
        
    } while (elapsed_us < nus);
}

/**
 * @brief     毫秒延时
 * @param     nms: 要延时的毫秒数
 * @retval    无
 */
void delay_ms(uint16_t nms)
{
    if (nms == 0) return;
    
    // 对于毫秒延时，可以选择使用HAL_Delay或者delay_us
    // 使用HAL_Delay更节省CPU资源
    delay_us(nms * 1000);
    
    // 或者使用精确的微秒延时：
    // delay_us((uint32_t)nms * 1000);
}