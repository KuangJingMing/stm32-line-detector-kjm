#include "main.h"
#include "./BSP/QSPI/qspi.h"
#include "stdio.h"


void test_flash_step_by_step(void)
{
    printf("=== 分步测试Flash操作 ===\n");
   
    
    // 准备测试数据
    uint8_t test_data[512];
    uint8_t read_data[512];
    
    for(int i = 0; i < 512; i++) {
        test_data[i] = i & 0xFF;
    }
   
    printf("步骤1：擦除扇区0\n");
    W25QXX_Erase_Sector(0);
    
    printf("步骤2：写入第一页（地址0x000）\n");
    W25QXX_Write(test_data, 0x000, 256);
    
    printf("步骤3：读取第一页验证\n");
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
    
    if(!page1_ok) {
        printf("第一页写入失败，停止测试\n");
        return;
    }
    
    printf("步骤4：写入第二页（地址0x100）\n");
    W25QXX_Write(&test_data[256], 0x100, 256);
    
    printf("步骤5：读取第二页验证\n");
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
    
    printf("=== 测试完成 ===\n");
}
