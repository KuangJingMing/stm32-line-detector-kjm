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
    LINE_DETECTOR_ERROR = 1
} LineDetector_Status_t;

// 检测配置结构体
typedef struct {
    uint8_t total_pins;               // 总引脚数
    uint8_t delay_ms;                 // 延时时间(ms)
} LineDetector_Config_t;

// 引脚映射关系结构体
typedef struct {
    uint8_t a_pin;  // A端引脚
    uint8_t b_pin;  // B端引脚
} LineDetector_PinMapping_t;

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


// 新增：用于存储每个A端引脚的响应模式
typedef struct {
    uint8_t a_pin;
    uint8_t response_pins[MAX_PINS];  // 响应的B端引脚列表
    uint8_t response_count;           // 响应的B端引脚数量
    uint32_t response_pattern;        // 响应模式的位掩码表示
} PinResponsePattern_t;


// 函数声明
LineDetector_Status_t LineDetector_Init(void);
LineDetector_Status_t LineDetector_LearnMapping(char *report_buffer, size_t buffer_size);
LineDetector_Status_t LineDetector_SetMapping(const LineDetector_PinMapping_t* mappings, uint16_t count);
LineDetector_Status_t LineDetector_RunTest(void);
LineDetector_Status_t LineDetector_TestSinglePin(uint8_t a_pin, uint8_t* result_b_pin);

LineDetector_Result_t* LineDetector_GetResult(void);
LineDetector_Config_t* LineDetector_GetConfig(void);
LineDetector_Status_t LineDetector_SetConfig(const LineDetector_Config_t* config);

static void LineDetector_AnalyzePinResult(uint8_t a_pin, uint8_t expected_b_pin, uint8_t* b_input);
static int LineDetector_GenerateReport(char *buffer, size_t buffer_size);

void LineDetector_App_Main(void);

extern char report_buffer[2048];
extern LineDetector_Status_t study_state;

#endif /* __LINE_DETECTOR_APP_H__ */
