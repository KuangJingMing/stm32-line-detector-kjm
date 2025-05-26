#include "main.h"
#include <stdio.h>
#include "./BSP/HC595/hc595.h"
#include "./BSP/HC165/hc165.h"


/**
 * @brief 简单的HC595到HC165测试
 */
void HC595_HC165_SimpleTest(void)
{
    uint8_t hc595_output[HC595_TOTAL_PINS]; // 595输出状态数组
    uint8_t hc165_input[HC165_TOTAL_PINS];  // 165输入状态数组

    // 初始化HC595和HC165
    HC595_Init();
    HC165_Init();
    
    // 清空数组
    memset(hc595_output, 1, sizeof(hc595_output));
    memset(hc165_input, 0, sizeof(hc165_input));
    
		HC595_SetPins(hc595_output);
    
    // 短暂延时确保输出稳定
    HAL_Delay(100);
    
    // 读取HC165输入
    HC165_ReadPins(hc165_input);

		
    // 比较输出和输入
    uint8_t mismatch_count = 0;
    for (int i = 0; i < HC595_TOTAL_PINS && i < 100; i++)
    {
        if (hc595_output[i] != hc165_input[i])
        {
            mismatch_count++;
            printf("Mismatch at Pin %d: Output=%d, Input=%d\r\n", 
                   i, hc595_output[i], hc165_input[i]);
        }
    }
    
    if (mismatch_count == 0)
    {
        printf("Test Passed: All Pins Match!\r\n");
    }
    else
    {
        printf("Test Failed: %d Mismatches Found!\r\n", mismatch_count);
    }
    
    // 停止测试，进入死循环
    while (1)
    {
        HAL_Delay(1000);
    }
}

void rg_test(void)
{
    HC595_HC165_SimpleTest();
    while (1)
    {
        // 永不返回
    }
}
