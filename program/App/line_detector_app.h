#ifndef __LINE_DETECTOR_APP_H__
#define __LINE_DETECTOR_APP_H__

#include "main.h"
#include <stdint.h>
#include "string.h"

// �������������
#define MAX_PINS 100

// �����״̬ö��
typedef enum {
    LINE_DETECTOR_OK = 0,
    LINE_DETECTOR_ERROR = 1
} LineDetector_Status_t;

// ������ýṹ��
typedef struct {
    uint8_t total_pins;               // ��������
    uint8_t delay_ms;                 // ��ʱʱ��(ms)
} LineDetector_Config_t;

// ����ӳ���ϵ�ṹ��
typedef struct {
    uint8_t a_pin;  // A������
    uint8_t b_pin;  // B������
} LineDetector_PinMapping_t;

// ��λ������Ϣ
typedef struct {
    uint8_t a_pin;                    // A������
    uint8_t expected_b;               // ������B������
    uint8_t actual_b;                 // ʵ�ʵ�B������
} MisplacedPin_t;

// ��·��Ϣ
typedef struct {
    uint8_t a_pin;                    // A������
    uint8_t b_pins[MAX_PINS];         // ��·��B����������
    uint8_t short_count;              // ��·��������
} ShortPin_t;

// ������ṹ��
typedef struct {
    uint8_t normal_count;             // ������������
    uint8_t open_circuit_count;       // ��·����
    uint8_t short_circuit_count;      // ��·����
    uint8_t misplaced_count;          // ��λ����
    
    uint8_t open_pins[MAX_PINS];      // ��·�����б�
    ShortPin_t short_pins[MAX_PINS];  // ��·��Ϣ�б�
    MisplacedPin_t misplaced_pins[MAX_PINS]; // ��λ��Ϣ�б�
} LineDetector_Result_t;


// ���������ڴ洢ÿ��A�����ŵ���Ӧģʽ
typedef struct {
    uint8_t a_pin;
    uint8_t response_pins[MAX_PINS];  // ��Ӧ��B�������б�
    uint8_t response_count;           // ��Ӧ��B����������
    uint32_t response_pattern;        // ��Ӧģʽ��λ�����ʾ
} PinResponsePattern_t;


// ��������
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
