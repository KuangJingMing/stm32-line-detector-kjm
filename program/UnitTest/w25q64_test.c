#include "main.h"
#include "./BSP/QSPI/qspi.h"
#include "stdio.h"


void test_flash_step_by_step(void)
{
    printf("=== �ֲ�����Flash���� ===\n");
   
    
    // ׼����������
    uint8_t test_data[512];
    uint8_t read_data[512];
    
    for(int i = 0; i < 512; i++) {
        test_data[i] = i & 0xFF;
    }
   
    printf("����1����������0\n");
    W25QXX_Erase_Sector(0);
    
    printf("����2��д���һҳ����ַ0x000��\n");
    W25QXX_Write(test_data, 0x000, 256);
    
    printf("����3����ȡ��һҳ��֤\n");
    W25QXX_Read(read_data, 0x000, 256);
    int page1_ok = 1;
    for(int i = 0; i < 256; i++) {
        if(read_data[i] != test_data[i]) {
            printf("��һҳ��֤ʧ�ܣ�ƫ�� %d: ���� 0x%02X, ʵ�� 0x%02X\n", 
                  i, test_data[i], read_data[i]);
            page1_ok = 0;
            if(i > 5) break;
        }
    }
    printf("��һҳ���: %s\n", page1_ok ? "�ɹ�" : "ʧ��");
    
    if(!page1_ok) {
        printf("��һҳд��ʧ�ܣ�ֹͣ����\n");
        return;
    }
    
    printf("����4��д��ڶ�ҳ����ַ0x100��\n");
    W25QXX_Write(&test_data[256], 0x100, 256);
    
    printf("����5����ȡ�ڶ�ҳ��֤\n");
    W25QXX_Read(read_data, 0x100, 256);
    int page2_ok = 1;
    for(int i = 0; i < 256; i++) {
        if(read_data[i] != test_data[256 + i]) {
            printf("�ڶ�ҳ��֤ʧ�ܣ�ƫ�� %d: ���� 0x%02X, ʵ�� 0x%02X\n", 
                  i, test_data[256 + i], read_data[i]);
            page2_ok = 0;
            if(i > 5) break;
        }
    }
    printf("�ڶ�ҳ���: %s\n", page2_ok ? "�ɹ�" : "ʧ��");
    
    printf("=== ������� ===\n");
}
