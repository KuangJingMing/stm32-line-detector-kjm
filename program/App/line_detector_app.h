#ifndef __LINE_DETECTOR_APP_H__
#define __LINE_DETECTOR_APP_H__

#include "main.h"
#include <stdint.h>
#include "string.h"

// 最大引脚数定义
#define MAX_PINS 100

// 检测器状态枚举
typedef enum {
    LINE_DETECTOR_OK = 0,
    LINE_DETECTOR_ERROR = 1,
    LINE_DETECTOR_BUSY = 2
} LineDetector_Status_t;

// 测试电压枚举
typedef enum {
    TEST_VOLTAGE_3V3 = 0,
    TEST_VOLTAGE_5V = 1
} LineDetector_Voltage_t;

// 检测配置结构体
typedef struct {
    uint8_t total_pins;               // 总引脚数
    LineDetector_Voltage_t test_voltage; // 测试电压
    uint8_t delay_ms;                 // 延时时间(ms)
    uint8_t retry_count;              // 重试次数
} LineDetector_Config_t;

// 错位连接信息
typedef struct {
    uint8_t a_pin;                    // A端引脚
    uint8_t expected_b;               // 期望的B端引脚
    uint8_t actual_b;                 // 实际的B端引脚
} MisplacedPin_t;

// 短路信息
typedef struct {
    uint8_t a_pin;                    // A端引脚
    uint8_t b_pins[MAX_PINS];         // 短路的B端引脚数组
    uint8_t short_count;              // 短路引脚数量
} ShortPin_t;

// 检测结果结构体
typedef struct {
    uint8_t normal_count;             // 正常连接数量
    uint8_t open_circuit_count;       // 断路数量
    uint8_t short_circuit_count;      // 短路数量
    uint8_t misplaced_count;          // 错位数量
    
    uint8_t open_pins[MAX_PINS];      // 断路引脚列表
    ShortPin_t short_pins[MAX_PINS];  // 短路信息列表
    MisplacedPin_t misplaced_pins[MAX_PINS]; // 错位信息列表
} LineDetector_Result_t;

// 函数声明
LineDetector_Status_t LineDetector_Init(void);
LineDetector_Status_t LineDetector_LearnGolden(void);
LineDetector_Status_t LineDetector_RunTest(void);
LineDetector_Status_t LineDetector_TestSinglePin(uint8_t a_pin, uint8_t* result_b_pin);
LineDetector_Status_t LineDetector_SetConfig(const LineDetector_Config_t* config);

LineDetector_Config_t* LineDetector_GetConfig(void);
LineDetector_Result_t* LineDetector_GetResult(void);

void LineDetector_App_Main(void);

// 内部函数声明
static void LineDetector_AnalyzePinResult(uint8_t a_pin, uint8_t* b_input);
static void LineDetector_GenerateReport(void);

#endif /* __LINE_DETECTOR_APP_H__ */
