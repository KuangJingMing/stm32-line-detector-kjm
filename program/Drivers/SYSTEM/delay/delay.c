#include "./SYSTEM/delay/delay.h"
#include "stm32h7xx_hal.h"

static TIM_HandleTypeDef htim3;
static uint32_t g_us_tick_overflow = 0;  // �������

/**
 * @brief     TIM3��ʼ��Ϊ΢�������
 */
static void TIM3_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    
    // ʹ��TIM3ʱ��
    __HAL_RCC_TIM3_CLK_ENABLE();
    
    // ��ȡTIM3��ʱ��Ƶ��
    uint32_t tim_clk = HAL_RCC_GetPCLK1Freq();
    
    // ���APB1Ԥ��Ƶ
    RCC_ClkInitTypeDef clk_init;
    uint32_t flash_latency;
    HAL_RCC_GetClockConfig(&clk_init, &flash_latency);
    
    if (clk_init.APB1CLKDivider != RCC_HCLK_DIV1)
    {
        tim_clk *= 2;
    }
    
    // TIM3��16λ��ʱ��������Ϊ1MHz����Ƶ��
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = (tim_clk / 1000000) - 1;  // Ԥ��Ƶ��1MHz
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 0xFFFF;  // 16λ���ֵ������32λ��
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {

    }
    
    // ����ʱ��Դ
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
    {

    }
    
    // ������ʱ��
    if (HAL_TIM_Base_Start(&htim3) != HAL_OK)
    {

    }
}

/**
 * @brief     ��ʼ���ӳٺ���
 * @param     ��
 * @retval    ��
 */
void delay_init(void)
{
    // ��ʼ��TIM3
    TIM3_Init();
}

/**
 * @brief     ��ȡ��ǰ΢�����ֵ
 */
static uint32_t get_us_tick(void)
{
    return __HAL_TIM_GET_COUNTER(&htim3);
}

/**
 * @brief     ��ȷ΢����ʱ�������棩
 */
void delay_us(uint32_t nus)
{
    uint32_t start_tick, current_tick, elapsed_us;
    
    if (nus == 0) return;
    
    // ���ڳ���ʱ���ֶδ���
    if (nus > 60000)  // ����60ms��HAL_Delay
    {
        HAL_Delay(nus / 1000);
        nus = nus % 1000;
        if (nus == 0) return;
    }
    
    start_tick = get_us_tick();
    
    do {
        current_tick = get_us_tick();
        
        // ����16λ���������
        if (current_tick >= start_tick)
        {
            elapsed_us = current_tick - start_tick;
        }
        else
        {
            // 16λ���������
            elapsed_us = (0xFFFF - start_tick) + current_tick + 1;
        }
        
    } while (elapsed_us < nus);
}

/**
 * @brief     ������ʱ
 * @param     nms: Ҫ��ʱ�ĺ�����
 * @retval    ��
 */
void delay_ms(uint16_t nms)
{
    if (nms == 0) return;
    
    // ���ں�����ʱ������ѡ��ʹ��HAL_Delay����delay_us
    // ʹ��HAL_Delay����ʡCPU��Դ
    delay_us(nms * 1000);
    
    // ����ʹ�þ�ȷ��΢����ʱ��
    // delay_us((uint32_t)nms * 1000);
}