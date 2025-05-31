#include "../App/line_detector_app.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include "./BSP/HC595/hc595.h"
#include "./BSP/HC165/hc165.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-source-encoding"

#define log(fmt, ...)  do {} while (0)

	
// 全局变量定义
static LineDetector_Config_t g_detector_config;
static LineDetector_Result_t g_detector_result;
static LineDetector_PinMapping_t g_pin_mappings[MAX_PINS]; // 引脚映射表
static uint16_t g_mapping_count = 0;                       // 映射数量
static PinResponsePattern_t g_response_patterns[MAX_PINS];
static uint16_t g_pattern_count = 0;

// 全局变量定义 外部调用
char report_buffer[2048];
LineDetector_Status_t study_state = LINE_DETECTOR_ERROR;

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
    g_detector_config.delay_ms = 20;

    // 清空结果
    memset(&g_detector_result, 0, sizeof(g_detector_result));

    // 清空映射表
    memset(g_pin_mappings, 0, sizeof(g_pin_mappings));
    g_mapping_count = 0;

    // 清空响应模式
    memset(g_response_patterns, 0, sizeof(g_response_patterns));
    g_pattern_count = 0;

    log("LineDetector Initialized Successfully!\r\n");
    return LINE_DETECTOR_OK;
}

/**
 * @brief 学习引脚映射关系（自动学习金样）
 * @param report_buffer 报告缓冲区指针
 * @param buffer_size 缓冲区大小
 */
LineDetector_Status_t LineDetector_LearnMapping(char *report_buffer, size_t buffer_size)
{
    uint8_t hc595_output[HC595_TOTAL_PINS];
    uint8_t hc165_input[HC165_TOTAL_PINS];
    uint16_t learn_success_count = 0;

    log("Starting Pin Mapping Learning...\r\n");
    
    // 清空报告缓冲区
    memset(report_buffer, 0, buffer_size);
    
    // 添加开始信息到报告
    snprintf(report_buffer, buffer_size, "=== 金样学习开始 ===\n总引脚数: %d\n\n", g_detector_config.total_pins);

    // 清空映射表
    memset(g_pin_mappings, 0, sizeof(g_pin_mappings));
    g_mapping_count = 0;

    // 逐一激励每个A端引脚进行学习
    for (int a_pin = 0; a_pin < g_detector_config.total_pins; a_pin++)
    {
        // 设置所有输出为高电平（默认状态）
        memset(hc595_output, 1, sizeof(hc595_output));

        // 只将当前A端引脚设为低电平（激励）
        hc595_output[a_pin] = 0;

        // 输出到HC595
        HC595_SetPins(hc595_output);

        // 延时稳定
        HAL_Delay(g_detector_config.delay_ms);

        // 读取HC165输入状态
        HC165_ReadPins(hc165_input);

        // 分析B端响应，寻找对应的B端引脚（输入为低电平表示连通）
        uint8_t response_count = 0;
        uint8_t response_pin = 0xFF;

        for (int b_pin = 0; b_pin < g_detector_config.total_pins; b_pin++)
        {
            if (hc165_input[b_pin] == 0) // 低电平表示连通
            {
                response_count++;
                response_pin = b_pin;
            }
        }

        // 学习判断逻辑
        if (response_count == 1)
        {
            // 正常：一对一映射
            g_pin_mappings[g_mapping_count].a_pin = a_pin;
            g_pin_mappings[g_mapping_count].b_pin = response_pin;
            g_mapping_count++;
            learn_success_count++;
            
            // 添加到报告缓冲区
            // snprintf(report_buffer + strlen(report_buffer), 
            //         buffer_size - strlen(report_buffer), 
            //         "A%d -> B%d (学习成功)\n", a_pin, response_pin);
            
            log("A%d -> B%d (Learned)\r\n", a_pin, response_pin);
        }
        else if (response_count == 0)
        {
            // 添加到报告缓冲区
            // snprintf(report_buffer + strlen(report_buffer), 
            //         buffer_size - strlen(report_buffer), 
            //         "A%d -> 无响应 (开路故障)\n", a_pin);
            
            log("A%d -> No Response (Open Circuit)\r\n", a_pin);
        }
        else
        {
            // 添加到报告缓冲区
            // snprintf(report_buffer + strlen(report_buffer), 
            //         buffer_size - strlen(report_buffer), 
            //         "A%d -> 多重响应 (短路故障)\n", a_pin);
            
            log("A%d -> Multiple Response (Short Circuit)\r\n", a_pin);
        }
    }

    // 恢复所有输出为高电平
    memset(hc595_output, 1, sizeof(hc595_output));
    HC595_SetPins(hc595_output);

    // 添加学习结果总结到报告
    snprintf(report_buffer + strlen(report_buffer), 
            buffer_size - strlen(report_buffer), 
            "\n=== 学习结果 ===\n成功学习: %d/%d\n成功率: %.1f%%\n", 
            learn_success_count, g_detector_config.total_pins,
            (float)learn_success_count / g_detector_config.total_pins * 100);

    // 学习完成判断
    if (learn_success_count >= g_detector_config.total_pins * 0.4) // 40%以上成功率认为学习完成
    {
        snprintf(report_buffer + strlen(report_buffer), 
                buffer_size - strlen(report_buffer), 
                "状态: 学习完成\n");
        
        log("Pin Mapping Learning Completed! Success Rate: %d/%d\r\n",
               learn_success_count, g_detector_config.total_pins);
        return LINE_DETECTOR_OK;
    }
    else
    {
        snprintf(report_buffer + strlen(report_buffer), 
                buffer_size - strlen(report_buffer), 
                "状态: 学习失败 (成功率过低)\n");
        
        log("Pin Mapping Learning Failed! Success Rate Too Low: %d/%d\r\n",
               learn_success_count, g_detector_config.total_pins);
        return LINE_DETECTOR_ERROR;
    }
}

/**
 * @brief 设置自定义引脚映射表
 */
LineDetector_Status_t LineDetector_SetMapping(const LineDetector_PinMapping_t *mappings, uint16_t count)
{
    if (mappings == NULL || count == 0 || count > MAX_PINS)
    {
        log("Error: Invalid mapping parameters!\r\n");
        return LINE_DETECTOR_ERROR;
    }

    // 验证引脚编号有效性
    for (uint16_t i = 0; i < count; i++)
    {
        if (mappings[i].a_pin >= g_detector_config.total_pins ||
            mappings[i].b_pin >= g_detector_config.total_pins)
        {
            log("Error: Invalid pin number in mapping %d (A%d->B%d)!\r\n",
                   i, mappings[i].a_pin, mappings[i].b_pin);
            return LINE_DETECTOR_ERROR;
        }
    }

    // 复制映射关系
    memcpy(g_pin_mappings, mappings, count * sizeof(LineDetector_PinMapping_t));
    g_mapping_count = count;

    log("Pin mapping table set successfully! Total mappings: %d\r\n", count);
    return LINE_DETECTOR_OK;
}

/**
 * @brief 改进的响应模式比较函数
 */
static uint8_t CompareResponsePatterns(const PinResponsePattern_t *pattern1,
                                       const PinResponsePattern_t *pattern2)
{
    // 首先比较响应数量
    if (pattern1->response_count != pattern2->response_count)
    {
        return 0; // 不匹配
    }

    // 逐个比较响应引脚（假设已排序）
    for (int i = 0; i < pattern1->response_count; i++)
    {
        if (pattern1->response_pins[i] != pattern2->response_pins[i])
        {
            return 0; // 不匹配
        }
    }

    return 1; // 匹配
}

/**
 * @brief 对响应引脚进行排序（便于比较）
 */
static void SortResponsePins(PinResponsePattern_t *pattern)
{
    // 简单冒泡排序
    for (int i = 0; i < pattern->response_count - 1; i++)
    {
        for (int j = 0; j < pattern->response_count - 1 - i; j++)
        {
            if (pattern->response_pins[j] > pattern->response_pins[j + 1])
            {
                uint8_t temp = pattern->response_pins[j];
                pattern->response_pins[j] = pattern->response_pins[j + 1];
                pattern->response_pins[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief 改进的响应模式收集函数
 */
static void LineDetector_CollectResponsePatterns(void)
{
    uint8_t hc595_output[HC595_TOTAL_PINS];
    uint8_t hc165_input[HC165_TOTAL_PINS];

    g_pattern_count = 0;
    memset(g_response_patterns, 0, sizeof(g_response_patterns));

    log("Collecting response patterns for all A pins...\r\n");

    // 逐一激励每个A端引脚，记录响应模式
    for (uint16_t i = 0; i < g_mapping_count; i++)
    {
        uint8_t a_pin = g_pin_mappings[i].a_pin;

        // 设置所有输出为高电平
        memset(hc595_output, 1, sizeof(hc595_output));

        // 只将当前A端引脚设为低电平
        hc595_output[a_pin] = 0;

        // 输出到HC595
        HC595_SetPins(hc595_output);

        // 延时稳定
        HAL_Delay(g_detector_config.delay_ms);

        // 读取HC165输入状态
        HC165_ReadPins(hc165_input);
        for (int i = 0; i < 100; i++)
        {
            log("%d ", hc165_input[i]);
        }
        log("\n");
        // 记录响应模式
        g_response_patterns[g_pattern_count].a_pin = a_pin;
        g_response_patterns[g_pattern_count].response_count = 0;
        g_response_patterns[g_pattern_count].response_pattern = 0;

        // 统计所有低电平的B端引脚（包括短路情况）
        for (int b_pin = 0; b_pin < g_detector_config.total_pins; b_pin++)
        {
            if (hc165_input[b_pin] == 0) // 低电平表示连通
            {
                uint8_t count = g_response_patterns[g_pattern_count].response_count;
                if (count < MAX_PINS) // 防止数组越界
                {
                    g_response_patterns[g_pattern_count].response_pins[count] = b_pin;
                    g_response_patterns[g_pattern_count].response_count++;

                    // 设置响应模式位掩码（仅支持前32个引脚的位掩码表示）
                    if (b_pin < 32)
                    {
                        g_response_patterns[g_pattern_count].response_pattern |= (1U << b_pin);
                    }
                }
            }
        }

        // 调试输出
        log("A%d -> Response count: %d, B pins: ", a_pin, g_response_patterns[g_pattern_count].response_count);
        for (int j = 0; j < g_response_patterns[g_pattern_count].response_count; j++)
        {
            log("B%d ", g_response_patterns[g_pattern_count].response_pins[j]);
        }
        log("\r\n");

        g_pattern_count++;
    }

    // 恢复所有输出为高电平
    memset(hc595_output, 1, sizeof(hc595_output));
    HC595_SetPins(hc595_output);
}

/**
 * @brief 改进的短路关系分析函数
 */
static void LineDetector_AnalyzeShortCircuits(void)
{
    log("Analyzing short circuit relationships...\r\n");

    // 对所有响应模式的引脚列表进行排序
    for (uint16_t i = 0; i < g_pattern_count; i++)
    {
        SortResponsePins(&g_response_patterns[i]);
    }

    // 用于标记已经处理过的A端引脚
    uint8_t processed[MAX_PINS] = {0};

    for (uint16_t i = 0; i < g_pattern_count; i++)
    {
        if (processed[i])
        {
            continue; // 已处理
        }

        // 检查是否存在多个响应（可能的短路）
        if (g_response_patterns[i].response_count > 1)
        {
            // 寻找具有相同响应模式的其他A端引脚
            uint8_t short_group[MAX_PINS];
            uint8_t short_group_count = 0;

            short_group[short_group_count++] = g_response_patterns[i].a_pin;
            processed[i] = 1;

            for (uint16_t j = i + 1; j < g_pattern_count; j++)
            {
                if (processed[j])
                {
                    continue;
                }

                // 使用改进的比较函数
                if (CompareResponsePatterns(&g_response_patterns[i], &g_response_patterns[j]))
                {
                    short_group[short_group_count++] = g_response_patterns[j].a_pin;
                    processed[j] = 1;
                }
            }

            // 记录短路组
            if (g_detector_result.short_circuit_count < MAX_PINS)
            {
                uint8_t idx = g_detector_result.short_circuit_count;

                // 记录短路的A端引脚组
                g_detector_result.short_pins[idx].a_pin = short_group[0]; // 主引脚
                g_detector_result.short_pins[idx].short_count = g_response_patterns[i].response_count;

                // 记录响应的B端引脚
                for (int k = 0; k < g_response_patterns[i].response_count && k < MAX_PINS; k++)
                {
                    g_detector_result.short_pins[idx].b_pins[k] = g_response_patterns[i].response_pins[k];
                }

                g_detector_result.short_circuit_count++;
            }

            // 打印短路信息
            log("Short Circuit Group %d (%d A-pins): ",
                   g_detector_result.short_circuit_count, short_group_count);
            for (int k = 0; k < short_group_count; k++)
            {
                log("A%d ", short_group[k]);
            }
            log("-> B-pins: ");
            for (int k = 0; k < g_response_patterns[i].response_count; k++)
            {
                log("B%d ", g_response_patterns[i].response_pins[k]);
            }
            log("\r\n");
        }
        else
        {
            // 单个响应或无响应的情况，在后续分析中处理
            processed[i] = 1;
        }
    }
}

/**
 * @brief 修正的主检测函数
 */
LineDetector_Status_t LineDetector_RunTest(void)
{
    if (g_mapping_count == 0)
    {
        log("Error: Pin mapping not set! Please learn or set mapping first.\r\n");
        return LINE_DETECTOR_ERROR;
    }

    // 清空检测结果
    memset(&g_detector_result, 0, sizeof(g_detector_result));

    log("Starting Line Bundle Detection...\r\n");
    log("Testing %d pin mappings...\r\n", g_mapping_count);

    // 第一步：收集所有A端引脚的响应模式
    LineDetector_CollectResponsePatterns();

    // 第二步：分析短路关系
    LineDetector_AnalyzeShortCircuits();

    // 第三步：分析其他故障类型（断路、错位）
    // 用于标记已经在短路分析中处理过的引脚
    uint8_t short_processed[MAX_PINS] = {0};

    // 标记短路组中的引脚
    for (uint16_t i = 0; i < g_pattern_count; i++)
    {
        if (g_response_patterns[i].response_count > 1)
        {
            // 查找具有相同响应模式的所有引脚
            for (uint16_t j = 0; j < g_pattern_count; j++)
            {
                if (CompareResponsePatterns(&g_response_patterns[i], &g_response_patterns[j]))
                {
                    short_processed[j] = 1;
                }
            }
        }
    }

    // 处理非短路情况
    for (uint16_t i = 0; i < g_pattern_count; i++)
    {
        if (short_processed[i])
        {
            continue; // 已在短路分析中处理
        }

        uint8_t a_pin = g_response_patterns[i].a_pin;
        uint8_t expected_b_pin = 0xFF;

        // 找到期望的B端引脚
        for (uint16_t j = 0; j < g_mapping_count; j++)
        {
            if (g_pin_mappings[j].a_pin == a_pin)
            {
                expected_b_pin = g_pin_mappings[j].b_pin;
                break;
            }
        }

        if (g_response_patterns[i].response_count == 0)
        {
            // 断路
            if (g_detector_result.open_circuit_count < MAX_PINS)
            {
                g_detector_result.open_pins[g_detector_result.open_circuit_count] = a_pin;
                g_detector_result.open_circuit_count++;
            }
            log("A%d: Open Circuit (Expected B%d)\r\n", a_pin, expected_b_pin);
        }
        else if (g_response_patterns[i].response_count == 1)
        {
            uint8_t actual_b_pin = g_response_patterns[i].response_pins[0];
            if (actual_b_pin == expected_b_pin)
            {
                // 正常连接
                g_detector_result.normal_count++;
                log("A%d -> B%d: Normal\r\n", a_pin, actual_b_pin);
            }
            else
            {
                // 错位
                if (g_detector_result.misplaced_count < MAX_PINS)
                {
                    g_detector_result.misplaced_pins[g_detector_result.misplaced_count].a_pin = a_pin;
                    g_detector_result.misplaced_pins[g_detector_result.misplaced_count].expected_b = expected_b_pin;
                    g_detector_result.misplaced_pins[g_detector_result.misplaced_count].actual_b = actual_b_pin;
                    g_detector_result.misplaced_count++;
                }
                log("A%d: Misplaced (Expected B%d, Actual B%d)\r\n",
                       a_pin, expected_b_pin, actual_b_pin);
            }
        }
    }

    // 生成检测报告
    int written_bytes = LineDetector_GenerateReport(report_buffer, sizeof(report_buffer));
    log("Line Bundle Detection Completed!\r\n");
    return LINE_DETECTOR_OK;
}

/**
 * @brief 生成检测报告到缓冲区
 * @param buffer 输出缓冲区
 * @param buffer_size 缓冲区大小
 * @return 实际写入的字符数
 */
static int LineDetector_GenerateReport(char *buffer, size_t buffer_size)
{
    int offset = 0;

    // 报告头部
    offset += snprintf(buffer + offset, buffer_size - offset,
                       "\r\n=== 线束检测报告 ===\r\n");
    offset += snprintf(buffer + offset, buffer_size - offset,
                       "测试映射总数: %d\r\n", g_mapping_count);
    offset += snprintf(buffer + offset, buffer_size - offset,
                       "正常连接: %d\r\n", g_detector_result.normal_count);
    offset += snprintf(buffer + offset, buffer_size - offset,
                       "开路故障: %d\r\n", g_detector_result.open_circuit_count);
    offset += snprintf(buffer + offset, buffer_size - offset,
                       "短路故障: %d\r\n", g_detector_result.short_circuit_count);
    offset += snprintf(buffer + offset, buffer_size - offset,
                       "错位连接: %d\r\n", g_detector_result.misplaced_count);

    // 开路故障详细信息
    if (g_detector_result.open_circuit_count > 0)
    {
        offset += snprintf(buffer + offset, buffer_size - offset,
                           "\r\n--- 开路故障详情 ---\r\n");
        for (int i = 0; i < g_detector_result.open_circuit_count; i++)
        {
            offset += snprintf(buffer + offset, buffer_size - offset,
                               "A%d: 开路\r\n", g_detector_result.open_pins[i]);
        }
    }

    // 短路故障详细信息
    if (g_detector_result.short_circuit_count > 0)
    {
        offset += snprintf(buffer + offset, buffer_size - offset,
                           "\r\n--- 短路故障详情 ---\r\n");
        for (int i = 0; i < g_detector_result.short_circuit_count; i++)
        {
            offset += snprintf(buffer + offset, buffer_size - offset,
                               "短路组 %d:\r\n", i + 1);

            // 找到所有具有相同响应模式的A端引脚
            uint32_t pattern = 0;
            for (int k = 0; k < g_detector_result.short_pins[i].short_count && k < 32; k++)
            {
                pattern |= (1U << g_detector_result.short_pins[i].b_pins[k]);
            }

            offset += snprintf(buffer + offset, buffer_size - offset,
                               "  涉及A端引脚: ");
            for (int j = 0; j < g_pattern_count; j++)
            {
                if (g_response_patterns[j].response_pattern == pattern &&
                    g_response_patterns[j].response_count > 1)
                {
                    offset += snprintf(buffer + offset, buffer_size - offset,
                                       "A%d ", g_response_patterns[j].a_pin);
                }
            }

            offset += snprintf(buffer + offset, buffer_size - offset,
                               "\r\n  影响B端引脚: ");
            for (int j = 0; j < g_detector_result.short_pins[i].short_count; j++)
            {
                offset += snprintf(buffer + offset, buffer_size - offset,
                                   "B%d ", g_detector_result.short_pins[i].b_pins[j]);
            }
            offset += snprintf(buffer + offset, buffer_size - offset, "\r\n");
        }
    }

    // 错位连接详细信息
    if (g_detector_result.misplaced_count > 0)
    {
        offset += snprintf(buffer + offset, buffer_size - offset,
                           "\r\n--- 错位连接详情 ---\r\n");
        for (int i = 0; i < g_detector_result.misplaced_count; i++)
        {
            offset += snprintf(buffer + offset, buffer_size - offset,
                               "A%d: 期望B%d, 实际B%d\r\n",
                               g_detector_result.misplaced_pins[i].a_pin,
                               g_detector_result.misplaced_pins[i].expected_b,
                               g_detector_result.misplaced_pins[i].actual_b);
        }
    }

    // 计算通过率
    float pass_rate = (float)g_detector_result.normal_count / g_mapping_count * 100.0f;
    offset += snprintf(buffer + offset, buffer_size - offset,
                       "\r\n通过率: %.1f%% (%d/%d)\r\n",
                       pass_rate, g_detector_result.normal_count, g_mapping_count);

    if (pass_rate >= 100.0f)
    {
        offset += snprintf(buffer + offset, buffer_size - offset, "检测结果: 合格\r\n");
    }
    else
    {
        offset += snprintf(buffer + offset, buffer_size - offset, "检测结果: 不合格\r\n");
    }

    offset += snprintf(buffer + offset, buffer_size - offset,
                       "=====================================\r\n\r\n");

    return offset;
}

/**
 * @brief 快速测试单个引脚连接
 */
LineDetector_Status_t LineDetector_TestSinglePin(uint8_t a_pin, uint8_t *result_b_pin)
{
    if (a_pin >= g_detector_config.total_pins || result_b_pin == NULL)
    {
        return LINE_DETECTOR_ERROR;
    }

    uint8_t hc595_output[HC595_TOTAL_PINS];
    uint8_t hc165_input[HC165_TOTAL_PINS];

    // 设置所有输出为高电平
    memset(hc595_output, 1, sizeof(hc595_output));

    // 只将指定A端引脚设为低电平
    hc595_output[a_pin] = 0;

    // 输出到HC595
    HC595_SetPins(hc595_output);

    // 延时稳定
    HAL_Delay(g_detector_config.delay_ms);

    // 读取HC165输入状态
    HC165_ReadPins(hc165_input);

    // 恢复所有输出为高电平
    memset(hc595_output, 1, sizeof(hc595_output));
    HC595_SetPins(hc595_output);

    // 分析结果
    *result_b_pin = 0xFF; // 默认无响应
    for (int b_pin = 0; b_pin < g_detector_config.total_pins; b_pin++)
    {
        if (hc165_input[b_pin] == 0) // 低电平表示连通
        {
            *result_b_pin = b_pin;
            break;
        }
    }

    return LINE_DETECTOR_OK;
}

/**
 * @brief 获取检测结果
 */
LineDetector_Result_t *LineDetector_GetResult(void)
{
    return &g_detector_result;
}

/**
 * @brief 设置检测参数
 */
LineDetector_Status_t LineDetector_SetConfig(const LineDetector_Config_t *config)
{
    if (config == NULL)
    {
        return LINE_DETECTOR_ERROR;
    }

    memcpy(&g_detector_config, config, sizeof(LineDetector_Config_t));
    log("Detector configuration updated.\r\n");
    return LINE_DETECTOR_OK;
}

/**
 * @brief 获取当前配置
 */
LineDetector_Config_t *LineDetector_GetConfig(void)
{
    return &g_detector_config;
}

void LineDetector_App_Main(void)
{
    log("=== Line Bundle Detector Application ===\r\n");

    // 初始化检测器
    if (LineDetector_Init() != LINE_DETECTOR_OK)
    {
        log("Detector initialization failed!\r\n");
        return;
    }

    // 设置1:1映射关系 (A0->B0, A1->B1, ...)
    log("\r\nStep 1: Setting 1:1 Pin Mapping\r\n");
    LineDetector_PinMapping_t map[MAX_PINS];
    for (int i = 0; i < MAX_PINS; i++)
    {
        map[i].a_pin = i;
        map[i].b_pin = i;
    }

    if (LineDetector_SetMapping(map, MAX_PINS) != LINE_DETECTOR_OK)
    {
        log("Pin mapping setup failed!\r\n");
        return;
    }

    // 等待用户准备测试样品
    log("\r\nStep 2: Please connect test sample and press any key to continue...\r\n");
    // getchar(); // 等待用户输入

    // 执行检测
    log("\r\nStep 3: Running Detection Test\r\n");
    if (LineDetector_RunTest() != LINE_DETECTOR_OK)
    {
        log("Detection test failed!\r\n");
        return;
    }

    log("Detection completed successfully!\r\n");

    // 进入循环等待下一次测试
    while (1)
    {
        HAL_Delay(1000);
        // 可在此处添加用户交互逻辑
    }
}

#pragma GCC diagnostic pop
