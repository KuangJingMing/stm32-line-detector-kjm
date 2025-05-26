#include "main.h"
#include <stdio.h>
#include "./BSP/HC595/hc595.h"
#include "./BSP/HC165/hc165.h"


/**
 * @brief �򵥵�HC595��HC165����
 */
void HC595_HC165_SimpleTest(void)
{
    uint8_t hc595_output[HC595_TOTAL_PINS]; // 595���״̬����
    uint8_t hc165_input[HC165_TOTAL_PINS];  // 165����״̬����

    // ��ʼ��HC595��HC165
    HC595_Init();
    HC165_Init();
    
    // �������
    memset(hc595_output, 1, sizeof(hc595_output));
    memset(hc165_input, 0, sizeof(hc165_input));
    
		HC595_SetPins(hc595_output);
    
    // ������ʱȷ������ȶ�
    HAL_Delay(100);
    
    // ��ȡHC165����
    HC165_ReadPins(hc165_input);

		
    // �Ƚ����������
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
    
    // ֹͣ���ԣ�������ѭ��
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
        // ��������
    }
}
