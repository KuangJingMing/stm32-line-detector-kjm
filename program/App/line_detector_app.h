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
    LINE_DETECTOR_ERROR = 1,
    LINE_DETECTOR_BUSY = 2
} LineDetector_Status_t;

// ���Ե�ѹö��
typedef enum {
    TEST_VOLTAGE_3V3 = 0,
    TEST_VOLTAGE_5V = 1
} LineDetector_Voltage_t;

// ������ýṹ��
typedef struct {
    uint8_t total_pins;               // ��������
    LineDetector_Voltage_t test_voltage; // ���Ե�ѹ
    uint8_t delay_ms;                 // ��ʱʱ��(ms)
    uint8_t retry_count;              // ���Դ���
} LineDetector_Config_t;

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

// ��������
LineDetector_Status_t LineDetector_Init(void);
LineDetector_Status_t LineDetector_LearnGolden(void);
LineDetector_Status_t LineDetector_RunTest(void);
LineDetector_Status_t LineDetector_TestSinglePin(uint8_t a_pin, uint8_t* result_b_pin);
LineDetector_Status_t LineDetector_SetConfig(const LineDetector_Config_t* config);

LineDetector_Config_t* LineDetector_GetConfig(void);
LineDetector_Result_t* LineDetector_GetResult(void);

void LineDetector_App_Main(void);

// �ڲ���������
static void LineDetector_AnalyzePinResult(uint8_t a_pin, uint8_t* b_input);
static void LineDetector_GenerateReport(void);

#endif /* __LINE_DETECTOR_APP_H__ */
