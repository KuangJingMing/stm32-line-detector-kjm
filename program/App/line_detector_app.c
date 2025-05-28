#include "../App/line_detector_app.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "./BSP/HC595/hc595.h"
#include "./BSP/HC165/hc165.h"

// 全局变量定义
static LineDetector_Config_t g_detector_config;
static LineDetector_Result_t g_detector_result;
static uint8_t g_golden_mapping[MAX_PINS];  // 金样映射表: A[i] -> B[j]
static uint8_t g_is_golden_learned = 0;     // 金样学习完成标志

/**
 * @brief 线束检测器初始化
 */
LineDetector_Status_t LineDetector_Init(void)
{
    // 初始化HC595输出锁存器
    HC595_Init();
    
    // 初始化HC165输入锁存器  
    HC165_Init();
    
    // 初始化配置参数
    g_detector_config.total_pins = 100;
    g_detector_config.test_voltage = TEST_VOLTAGE_3V3;
    g_detector_config.delay_ms = 10;
    g_detector_config.retry_count = 3;
    
    // 清空结果
    memset(&g_detector_result, 0, sizeof(g_detector_result));
    
    // 清空金样映射表
    memset(g_golden_mapping, 0xFF, sizeof(g_golden_mapping)); // 0xFF表示未映射
    g_is_golden_learned = 0;
    
    printf("LineDetector Initialized Successfully!\r\n");
    return LINE_DETECTOR_OK;
}

/**
 * @brief 金样学习过程
 */
LineDetector_Status_t LineDetector_LearnGolden(void)
{
    uint8_t hc595_output[HC595_TOTAL_PINS];
    uint8_t hc165_input[HC165_TOTAL_PINS];
    uint8_t learn_success_count = 0;
    
    printf("Starting Golden Sample Learning...\r\n");
    
    // 清空映射表
    memset(g_golden_mapping, 0xFF, sizeof(g_golden_mapping));
    
    // 逐一激励每个A端引脚进行学习
    for (int a_pin = 0; a_pin < g_detector_config.total_pins; a_pin++)
    {
        // 清空输出数组
        memset(hc595_output, 0, sizeof(hc595_output));
        
        // 只激励当前A端引脚
        hc595_output[a_pin] = 1;
        
        // 输出到HC595
        HC595_SetPins(hc595_output);
        
        // 延时稳定
        HAL_Delay(g_detector_config.delay_ms);
        
        // 读取HC165输入状态
        HC165_ReadPins(hc165_input);
        
        // 分析B端响应，寻找对应的B端引脚
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
        
        // 学习判断逻辑
        if (response_count == 1)
        {
            // 正常：一对一映射
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
    
    // 关闭所有输出
    memset(hc595_output, 0, sizeof(hc595_output));
    HC595_SetPins(hc595_output);
    
    // 学习完成判断
    if (learn_success_count >= g_detector_config.total_pins * 0.8) // 80%以上成功率认为学习完成
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
 * @brief 执行完整线束检测
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
    
    // 清空检测结果
    memset(&g_detector_result, 0, sizeof(g_detector_result));
    
    printf("Starting Line Bundle Detection...\r\n");
    
    // 逐一激励每个A端引脚进行检测
    for (int a_pin = 0; a_pin < g_detector_config.total_pins; a_pin++)
    {
        // 清空输出数组
        memset(hc595_output, 0, sizeof(hc595_output));
        
        // 只激励当前A端引脚
        hc595_output[a_pin] = 1;
        
        // 输出到HC595
        HC595_SetPins(hc595_output);
        
        // 延时稳定
        HAL_Delay(g_detector_config.delay_ms);
        
        // 读取HC165输入状态
        HC165_ReadPins(hc165_input);
        
        // 分析检测结果
        LineDetector_AnalyzePinResult(a_pin, hc165_input);
    }
    
    // 关闭所有输出
    memset(hc595_output, 0, sizeof(hc595_output));
    HC595_SetPins(hc595_output);
    
    // 生成检测报告
    LineDetector_GenerateReport();
    
    printf("Line Bundle Detection Completed!\r\n");
    return LINE_DETECTOR_OK;
}

/**
 * @brief 分析单个引脚的检测结果
 */
static void LineDetector_AnalyzePinResult(uint8_t a_pin, uint8_t* b_input)
{
    uint8_t expected_b_pin = g_golden_mapping[a_pin];
    uint8_t response_count = 0;
    uint8_t actual_b_pin = 0xFF;
    uint8_t short_pins[MAX_PINS];
    uint8_t short_count = 0;
    
    // 统计B端响应
    for (int b_pin = 0; b_pin < g_detector_config.total_pins; b_pin++)
    {
        if (b_input[b_pin] == 1)
        {
            response_count++;
            actual_b_pin = b_pin;
            short_pins[short_count++] = b_pin;
        }
    }
    
    // 根据响应情况判断故障类型
    if (response_count == 0)
    {
        // 断路检测
        g_detector_result.open_circuit_count++;
        g_detector_result.open_pins[g_detector_result.open_circuit_count - 1] = a_pin;
        printf("A%d: Open Circuit (Expected B%d)\r\n", a_pin, expected_b_pin);
    }
    else if (response_count == 1)
    {
        if (actual_b_pin == expected_b_pin)
        {
            // 正常连接
            g_detector_result.normal_count++;
            printf("A%d -> B%d: Normal\r\n", a_pin, actual_b_pin);
        }
        else
        {
            // 错位检测
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
        // 短路检测
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
 * @brief 生成检测报告
 */
static void LineDetector_GenerateReport(void)
{
    printf("\r\n=== LINE BUNDLE DETECTION REPORT ===\r\n");
    printf("Total Pins Tested: %d\r\n", g_detector_config.total_pins);
    printf("Normal Connections: %d\r\n", g_detector_result.normal_count);
    printf("Open Circuits: %d\r\n", g_detector_result.open_circuit_count);
    printf("Short Circuits: %d\r\n", g_detector_result.short_circuit_count);
    printf("Misplaced Connections: %d\r\n", g_detector_result.misplaced_count);
    
    // 详细故障信息
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
    
    // 计算通过率
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
 * @brief 获取检测结果
 */
LineDetector_Result_t* LineDetector_GetResult(void)
{
    return &g_detector_result;
}

/**
 * @brief 设置检测参数
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
 * @brief 获取当前配置
 */
LineDetector_Config_t* LineDetector_GetConfig(void)
{
    return &g_detector_config;
}

/**
 * @brief 快速测试单个引脚连接
 */
LineDetector_Status_t LineDetector_TestSinglePin(uint8_t a_pin, uint8_t* result_b_pin)
{
    if (a_pin >= g_detector_config.total_pins || result_b_pin == NULL)
    {
        return LINE_DETECTOR_ERROR;
    }
    
    uint8_t hc595_output[HC595_TOTAL_PINS];
    uint8_t hc165_input[HC165_TOTAL_PINS];
    
    // 清空输出数组
    memset(hc595_output, 0, sizeof(hc595_output));
    
    // 只激励指定A端引脚
    hc595_output[a_pin] = 1;
    
    // 输出到HC595
    HC595_SetPins(hc595_output);
    
    // 延时稳定
    HAL_Delay(g_detector_config.delay_ms);
    
    // 读取HC165输入状态
    HC165_ReadPins(hc165_input);
    
    // 关闭输出
    memset(hc595_output, 0, sizeof(hc595_output));
    HC595_SetPins(hc595_output);
    
    // 分析结果
    *result_b_pin = 0xFF; // 默认无响应
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
 * @brief 主应用入口函数
 */
void LineDetector_App_Main(void)
{
    printf("=== Line Bundle Detector Application ===\r\n");
    
    // 初始化检测器
    if (LineDetector_Init() != LINE_DETECTOR_OK)
    {
        printf("Detector initialization failed!\r\n");
        return;
    }
    
    // 金样学习
    printf("\r\nStep 1: Golden Sample Learning\r\n");
    if (LineDetector_LearnGolden() != LINE_DETECTOR_OK)
    {
        printf("Golden sample learning failed!\r\n");
        return;
    }
    
    // 等待用户准备测试样品
    printf("\r\nStep 2: Please connect test sample and press any key to continue...\r\n");
    
    while (1) {


    }
    
    // 执行检测
    printf("\r\nStep 3: Running Detection Test\r\n");
    if (LineDetector_RunTest() != LINE_DETECTOR_OK)
    {
        printf("Detection test failed!\r\n");
        return;
    }
    
    printf("Detection completed successfully!\r\n");
    
    // 进入循环等待下一次测试
    while (1)
    {
        HAL_Delay(1000);
        // 可在此处添加用户交互逻辑
    }
}
