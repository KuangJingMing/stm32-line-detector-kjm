#include "main.h"
#include "./BSP/QSPI/qspi.h"
#include "stdio.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-source-encoding"

// 条件编译开关：设置为1进行写入测试，设置为0仅读取验证
#define ENABLE_WRITE_TEST   0   // 第一次测试时设为1，第二次上电测试时设为0

void test_flash_step_by_step(void)
{
    printf("=== 分步测试Flash操作 ===\n");
   
    // 准备测试数据
    uint8_t test_data[512];
    uint8_t read_data[512];
    
    for(int i = 0; i < 512; i++) {
        test_data[i] = i & 0xFF;
    }

#if ENABLE_WRITE_TEST
    printf(">>> 写入模式：执行擦除和写入操作 <<<\n");
    
    printf("步骤1：擦除扇区0\n");
    W25QXX_Erase_Sector(0);
    
    printf("步骤2：写入第一页（地址0x000）\n");
    W25QXX_Write(test_data, 0x000, 256);
    
    printf("步骤3：写入第二页（地址0x100）\n");
    W25QXX_Write(&test_data[256], 0x100, 256);
    
    printf("写入操作完成，请重新编译（设置ENABLE_WRITE_TEST为0）并重新上电测试\n");
#else
    printf(">>> 验证模式：仅读取验证数据保持性 <<<\n");
    printf("正在验证上电后Flash数据是否保持...\n");
#endif

    // 读取验证部分（无论是否写入都会执行）
    printf("步骤%d：读取第一页验证\n", ENABLE_WRITE_TEST ? 4 : 1);
    W25QXX_Read(read_data, 0x000, 256);
    int page1_ok = 1;
    for(int i = 0; i < 256; i++) {
        if(read_data[i] != test_data[i]) {
            printf("第一页验证失败，偏移 %d: 期望 0x%02X, 实际 0x%02X\n", 
                  i, test_data[i], read_data[i]);
            page1_ok = 0;
            if(i > 5) break;
        }
    }
    printf("第一页结果: %s\n", page1_ok ? "成功" : "失败");
    
    printf("步骤%d：读取第二页验证\n", ENABLE_WRITE_TEST ? 5 : 2);
    W25QXX_Read(read_data, 0x100, 256);
    int page2_ok = 1;
    for(int i = 0; i < 256; i++) {
        if(read_data[i] != test_data[256 + i]) {
            printf("第二页验证失败，偏移 %d: 期望 0x%02X, 实际 0x%02X\n", 
                  i, test_data[256 + i], read_data[i]);
            page2_ok = 0;
            if(i > 5) break;
        }
    }
    printf("第二页结果: %s\n", page2_ok ? "成功" : "失败");
    
#if ENABLE_WRITE_TEST
    printf("=== 写入测试完成 ===\n");
    printf("提示：将 ENABLE_WRITE_TEST 改为 0 并重新上电测试数据保持性\n");
#else
    printf("=== 数据保持性测试完成 ===\n");
    if(page1_ok && page2_ok) {
        printf("Flash数据在断电重启后保持完好！\n");
    } else {
        printf("Flash数据在断电重启后丢失或损坏！\n");
    }
#endif
}

#pragma GCC diagnostic pop
