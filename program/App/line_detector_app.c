#include "../App/line_detector_app.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "./BSP/HC595/hc595.h"
#include "./BSP/HC165/hc165.h"

// ȫ�ֱ�������
static LineDetector_Config_t g_detector_config;
static LineDetector_Result_t g_detector_result;
static uint8_t g_golden_mapping[MAX_PINS];  // ����ӳ���: A[i] -> B[j]
static uint8_t g_is_golden_learned = 0;     // ����ѧϰ��ɱ�־

/**
 * @brief �����������ʼ��
 */
LineDetector_Status_t LineDetector_Init(void)
{
    // ��ʼ��HC595���������
    HC595_Init();
    
    // ��ʼ��HC165����������  
    HC165_Init();
    
    // ��ʼ�����ò���
    g_detector_config.total_pins = 100;
    g_detector_config.test_voltage = TEST_VOLTAGE_3V3;
    g_detector_config.delay_ms = 10;
    g_detector_config.retry_count = 3;
    
    // ��ս��
    memset(&g_detector_result, 0, sizeof(g_detector_result));
    
    // ��ս���ӳ���
    memset(g_golden_mapping, 0xFF, sizeof(g_golden_mapping)); // 0xFF��ʾδӳ��
    g_is_golden_learned = 0;
    
    printf("LineDetector Initialized Successfully!\r\n");
    return LINE_DETECTOR_OK;
}

/**
 * @brief ����ѧϰ����
 */
LineDetector_Status_t LineDetector_LearnGolden(void)
{
    uint8_t hc595_output[HC595_TOTAL_PINS];
    uint8_t hc165_input[HC165_TOTAL_PINS];
    uint8_t learn_success_count = 0;
    
    printf("Starting Golden Sample Learning...\r\n");
    
    // ���ӳ���
    memset(g_golden_mapping, 0xFF, sizeof(g_golden_mapping));
    
    // ��һ����ÿ��A�����Ž���ѧϰ
    for (int a_pin = 0; a_pin < g_detector_config.total_pins; a_pin++)
    {
        // ����������
        memset(hc595_output, 0, sizeof(hc595_output));
        
        // ֻ������ǰA������
        hc595_output[a_pin] = 1;
        
        // �����HC595
        HC595_SetPins(hc595_output);
        
        // ��ʱ�ȶ�
        HAL_Delay(g_detector_config.delay_ms);
        
        // ��ȡHC165����״̬
        HC165_ReadPins(hc165_input);
        
        // ����B����Ӧ��Ѱ�Ҷ�Ӧ��B������
        uint8_t response_count = 0;
        uint8_t response_pin = 0xFF;
        
        for (int b_pin = 0; b_pin < g_detector_config.total_pins; b_pin++)
        {
            if (hc165_input[b_pin] == 1)
            {
                response_count++;
                response_pin = b_pin;
            }
        }
        
        // ѧϰ�ж��߼�
        if (response_count == 1)
        {
            // ������һ��һӳ��
            g_golden_mapping[a_pin] = response_pin;
            learn_success_count++;
            printf("A%d -> B%d (Learned)\r\n", a_pin, response_pin);
        }
        else if (response_count == 0)
        {
            printf("A%d -> No Response (Open Circuit)\r\n", a_pin);
        }
        else
        {
            printf("A%d -> Multiple Response (Short Circuit)\r\n", a_pin);
        }
    }
    
    // �ر��������
    memset(hc595_output, 0, sizeof(hc595_output));
    HC595_SetPins(hc595_output);
    
    // ѧϰ����ж�
    if (learn_success_count >= g_detector_config.total_pins * 0.8) // 80%���ϳɹ�����Ϊѧϰ���
    {
        g_is_golden_learned = 1;
        printf("Golden Learning Completed! Success Rate: %d/%d\r\n", 
               learn_success_count, g_detector_config.total_pins);
        return LINE_DETECTOR_OK;
    }
    else
    {
        printf("Golden Learning Failed! Success Rate Too Low: %d/%d\r\n", 
               learn_success_count, g_detector_config.total_pins);
        return LINE_DETECTOR_ERROR;
    }
}

/**
 * @brief ִ�������������
 */
LineDetector_Status_t LineDetector_RunTest(void)
{
    if (!g_is_golden_learned)
    {
        printf("Error: Golden sample not learned yet!\r\n");
        return LINE_DETECTOR_ERROR;
    }
    
    uint8_t hc595_output[HC595_TOTAL_PINS];
    uint8_t hc165_input[HC165_TOTAL_PINS];
    
    // ��ռ����
    memset(&g_detector_result, 0, sizeof(g_detector_result));
    
    printf("Starting Line Bundle Detection...\r\n");
    
    // ��һ����ÿ��A�����Ž��м��
    for (int a_pin = 0; a_pin < g_detector_config.total_pins; a_pin++)
    {
        // ����������
        memset(hc595_output, 0, sizeof(hc595_output));
        
        // ֻ������ǰA������
        hc595_output[a_pin] = 1;
        
        // �����HC595
        HC595_SetPins(hc595_output);
        
        // ��ʱ�ȶ�
        HAL_Delay(g_detector_config.delay_ms);
        
        // ��ȡHC165����״̬
        HC165_ReadPins(hc165_input);
        
        // ���������
        LineDetector_AnalyzePinResult(a_pin, hc165_input);
    }
    
    // �ر��������
    memset(hc595_output, 0, sizeof(hc595_output));
    HC595_SetPins(hc595_output);
    
    // ���ɼ�ⱨ��
    LineDetector_GenerateReport();
    
    printf("Line Bundle Detection Completed!\r\n");
    return LINE_DETECTOR_OK;
}

/**
 * @brief �����������ŵļ����
 */
static void LineDetector_AnalyzePinResult(uint8_t a_pin, uint8_t* b_input)
{
    uint8_t expected_b_pin = g_golden_mapping[a_pin];
    uint8_t response_count = 0;
    uint8_t actual_b_pin = 0xFF;
    uint8_t short_pins[MAX_PINS];
    uint8_t short_count = 0;
    
    // ͳ��B����Ӧ
    for (int b_pin = 0; b_pin < g_detector_config.total_pins; b_pin++)
    {
        if (b_input[b_pin] == 1)
        {
            response_count++;
            actual_b_pin = b_pin;
            short_pins[short_count++] = b_pin;
        }
    }
    
    // ������Ӧ����жϹ�������
    if (response_count == 0)
    {
        // ��·���
        g_detector_result.open_circuit_count++;
        g_detector_result.open_pins[g_detector_result.open_circuit_count - 1] = a_pin;
        printf("A%d: Open Circuit (Expected B%d)\r\n", a_pin, expected_b_pin);
    }
    else if (response_count == 1)
    {
        if (actual_b_pin == expected_b_pin)
        {
            // ��������
            g_detector_result.normal_count++;
            printf("A%d -> B%d: Normal\r\n", a_pin, actual_b_pin);
        }
        else
        {
            // ��λ���
            g_detector_result.misplaced_count++;
            g_detector_result.misplaced_pins[g_detector_result.misplaced_count - 1].a_pin = a_pin;
            g_detector_result.misplaced_pins[g_detector_result.misplaced_count - 1].expected_b = expected_b_pin;
            g_detector_result.misplaced_pins[g_detector_result.misplaced_count - 1].actual_b = actual_b_pin;
            printf("A%d: Misplaced (Expected B%d, Actual B%d)\r\n", 
                   a_pin, expected_b_pin, actual_b_pin);
        }
    }
    else
    {
        // ��·���
        g_detector_result.short_circuit_count++;
        g_detector_result.short_pins[g_detector_result.short_circuit_count - 1].a_pin = a_pin;
        g_detector_result.short_pins[g_detector_result.short_circuit_count - 1].short_count = short_count;
        
        printf("A%d: Short Circuit to B-pins: ", a_pin);
        for (int i = 0; i < short_count; i++)
        {
            g_detector_result.short_pins[g_detector_result.short_circuit_count - 1].b_pins[i] = short_pins[i];
            printf("B%d ", short_pins[i]);
        }
        printf("\r\n");
    }
}

/**
 * @brief ���ɼ�ⱨ��
 */
static void LineDetector_GenerateReport(void)
{
    printf("\r\n=== LINE BUNDLE DETECTION REPORT ===\r\n");
    printf("Total Pins Tested: %d\r\n", g_detector_config.total_pins);
    printf("Normal Connections: %d\r\n", g_detector_result.normal_count);
    printf("Open Circuits: %d\r\n", g_detector_result.open_circuit_count);
    printf("Short Circuits: %d\r\n", g_detector_result.short_circuit_count);
    printf("Misplaced Connections: %d\r\n", g_detector_result.misplaced_count);
    
    // ��ϸ������Ϣ
    if (g_detector_result.open_circuit_count > 0)
    {
        printf("\r\n--- Open Circuit Details ---\r\n");
        for (int i = 0; i < g_detector_result.open_circuit_count; i++)
        {
            printf("A%d: Open Circuit\r\n", g_detector_result.open_pins[i]);
        }
    }
    
    if (g_detector_result.short_circuit_count > 0)
    {
        printf("\r\n--- Short Circuit Details ---\r\n");
        for (int i = 0; i < g_detector_result.short_circuit_count; i++)
        {
            printf("A%d: Short to ", g_detector_result.short_pins[i].a_pin);
            for (int j = 0; j < g_detector_result.short_pins[i].short_count; j++)
            {
                printf("B%d ", g_detector_result.short_pins[i].b_pins[j]);
            }
            printf("\r\n");
        }
    }
    
    if (g_detector_result.misplaced_count > 0)
    {
        printf("\r\n--- Misplaced Connection Details ---\r\n");
        for (int i = 0; i < g_detector_result.misplaced_count; i++)
        {
            printf("A%d: Expected B%d, Actual B%d\r\n",
                   g_detector_result.misplaced_pins[i].a_pin,
                   g_detector_result.misplaced_pins[i].expected_b,
                   g_detector_result.misplaced_pins[i].actual_b);
        }
    }
    
    // ����ͨ����
    float pass_rate = (float)g_detector_result.normal_count / g_detector_config.total_pins * 100.0f;
    printf("\r\nPass Rate: %.1f%%\r\n", pass_rate);
    
    if (pass_rate >= 95.0f)
    {
        printf("RESULT: PASS\r\n");
    }
    else
    {
        printf("RESULT: FAIL\r\n");
    }
    
    printf("=====================================\r\n\r\n");
}

/**
 * @brief ��ȡ�����
 */
LineDetector_Result_t* LineDetector_GetResult(void)
{
    return &g_detector_result;
}

/**
 * @brief ���ü�����
 */
LineDetector_Status_t LineDetector_SetConfig(const LineDetector_Config_t* config)
{
    if (config == NULL)
    {
        return LINE_DETECTOR_ERROR;
    }
    
    memcpy(&g_detector_config, config, sizeof(LineDetector_Config_t));
    printf("Detector configuration updated.\r\n");
    return LINE_DETECTOR_OK;
}

/**
 * @brief ��ȡ��ǰ����
 */
LineDetector_Config_t* LineDetector_GetConfig(void)
{
    return &g_detector_config;
}

/**
 * @brief ���ٲ��Ե�����������
 */
LineDetector_Status_t LineDetector_TestSinglePin(uint8_t a_pin, uint8_t* result_b_pin)
{
    if (a_pin >= g_detector_config.total_pins || result_b_pin == NULL)
    {
        return LINE_DETECTOR_ERROR;
    }
    
    uint8_t hc595_output[HC595_TOTAL_PINS];
    uint8_t hc165_input[HC165_TOTAL_PINS];
    
    // ����������
    memset(hc595_output, 0, sizeof(hc595_output));
    
    // ֻ����ָ��A������
    hc595_output[a_pin] = 1;
    
    // �����HC595
    HC595_SetPins(hc595_output);
    
    // ��ʱ�ȶ�
    HAL_Delay(g_detector_config.delay_ms);
    
    // ��ȡHC165����״̬
    HC165_ReadPins(hc165_input);
    
    // �ر����
    memset(hc595_output, 0, sizeof(hc595_output));
    HC595_SetPins(hc595_output);
    
    // �������
    *result_b_pin = 0xFF; // Ĭ������Ӧ
    for (int b_pin = 0; b_pin < g_detector_config.total_pins; b_pin++)
    {
        if (hc165_input[b_pin] == 1)
        {
            *result_b_pin = b_pin;
            break;
        }
    }
    
    return LINE_DETECTOR_OK;
}

/**
 * @brief ��Ӧ����ں���
 */
void LineDetector_App_Main(void)
{
    printf("=== Line Bundle Detector Application ===\r\n");
    
    // ��ʼ�������
    if (LineDetector_Init() != LINE_DETECTOR_OK)
    {
        printf("Detector initialization failed!\r\n");
        return;
    }
    
    // ����ѧϰ
    printf("\r\nStep 1: Golden Sample Learning\r\n");
    if (LineDetector_LearnGolden() != LINE_DETECTOR_OK)
    {
        printf("Golden sample learning failed!\r\n");
        return;
    }
    
    // �ȴ��û�׼��������Ʒ
    printf("\r\nStep 2: Please connect test sample and press any key to continue...\r\n");
    
    while (1) {


    }
    
    // ִ�м��
    printf("\r\nStep 3: Running Detection Test\r\n");
    if (LineDetector_RunTest() != LINE_DETECTOR_OK)
    {
        printf("Detection test failed!\r\n");
        return;
    }
    
    printf("Detection completed successfully!\r\n");
    
    // ����ѭ���ȴ���һ�β���
    while (1)
    {
        HAL_Delay(1000);
        // ���ڴ˴�����û������߼�
    }
}
