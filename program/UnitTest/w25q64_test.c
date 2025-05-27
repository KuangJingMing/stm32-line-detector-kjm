#include "main.h"
#include "./BSP/QSPI/qspi.h"

void W25QXX_Erase_Sector_Fixed(u32 Dst_Addr)   
{  
    u32 sector_addr = Dst_Addr * 4096;
    u8 sr3 = W25QXX_ReadSR(3);
    u8 erase_cmd;
    u8 addr_mode;
    
    // 检查地址模式
    if(sr3 & 0x01) {
        // 4字节地址模式
        erase_cmd = 0x21;  // 4字节扇区擦除命令
        addr_mode = (0<<6)|(3<<4)|(3<<2)|(3<<0);  // 32位地址
        printf("Using 4-byte sector erase command (0x21)\r\n");
    } else {
        // 3字节地址模式  
        erase_cmd = 0x20;  // 3字节扇区擦除命令
        addr_mode = (0<<6)|(2<<4)|(3<<2)|(3<<0);  // 24位地址
        printf("Using 3-byte sector erase command (0x20)\r\n");
    }
    
    printf("Erasing sector %lu, address 0x%08lX\r\n", Dst_Addr, sector_addr);
    
    // 写使能
    W25QXX_Write_Enable();
    
    // 检查写使能
    u8 status = W25QXX_ReadSR(1);
    printf("After write enable, status: 0x%02X\r\n", status);
    
    if((status & 0x02) == 0) {
        printf("ERROR: Write enable failed!\r\n");
        return;
    }
    
    // 等待不忙
    W25QXX_Wait_Busy();
    
    // 发送擦除命令
    printf("Sending erase command 0x%02X...\r\n", erase_cmd);
    QSPI_Send_CMD(erase_cmd, sector_addr, addr_mode, 0);
    
    // 等待擦除完成
    printf("Waiting for erase to complete...\r\n");
    W25QXX_Wait_Busy();
    
    // 检查最终状态
    status = W25QXX_ReadSR(1);
    printf("After erase, status: 0x%02X\r\n", status);
}


void check_address_mode(void)
{
    u8 sr3 = W25QXX_ReadSR(3);
    printf("SR3: 0x%02X\r\n", sr3);
    printf("Address Mode: %s\r\n", (sr3 & 0x01) ? "4-Byte" : "3-Byte");
    
    if(sr3 & 0x01) {
        printf("Flash is in 4-byte address mode\r\n");
    } else {
        printf("Flash is in 3-byte address mode\r\n");
    }
}


void check_protection_status(void)
{
    u8 sr1 = W25QXX_ReadSR(1);
    u8 sr2 = W25QXX_ReadSR(2);
    u8 sr3 = W25QXX_ReadSR(3);
    
    printf("=== Protection Status ===\r\n");
    printf("SR1: 0x%02X\r\n", sr1);
    printf("  BUSY: %d\r\n", (sr1 >> 0) & 1);
    printf("  WEL:  %d\r\n", (sr1 >> 1) & 1);
    printf("  BP0:  %d\r\n", (sr1 >> 2) & 1);
    printf("  BP1:  %d\r\n", (sr1 >> 3) & 1);
    printf("  BP2:  %d\r\n", (sr1 >> 4) & 1);
    printf("  TB:   %d\r\n", (sr1 >> 5) & 1);
    printf("  SEC:  %d\r\n", (sr1 >> 6) & 1);
    printf("  SRP0: %d\r\n", (sr1 >> 7) & 1);
    
    printf("SR2: 0x%02X\r\n", sr2);
    printf("  SRP1: %d\r\n", (sr2 >> 0) & 1);
    printf("  QE:   %d\r\n", (sr2 >> 1) & 1);
    printf("  LB1:  %d\r\n", (sr2 >> 3) & 1);
    printf("  LB2:  %d\r\n", (sr2 >> 4) & 1);
    printf("  LB3:  %d\r\n", (sr2 >> 5) & 1);
    printf("  CMP:  %d\r\n", (sr2 >> 6) & 1);
    printf("  SUS:  %d\r\n", (sr2 >> 7) & 1);
    
    printf("SR3: 0x%02X\r\n", sr3);
}

void force_3byte_mode(void)
{
    printf("Forcing 3-byte address mode...\r\n");
    
    // 退出4字节地址模式
    W25QXX_Write_Enable();
    QSPI_Send_CMD(0xE9, 0, (0<<6)|(0<<4)|(0<<2)|(3<<0), 0);  // Exit 4-byte mode
    
    // 检查结果
    u8 sr3 = W25QXX_ReadSR(3);
    printf("After exit 4-byte mode, SR3: 0x%02X\r\n", sr3);
    printf("Address Mode: %s\r\n", (sr3 & 0x01) ? "4-Byte" : "3-Byte");
}


void test_erase_with_address_mode(void)
{
    printf("=== Address Mode Test ===\r\n");
    
    // 检查当前地址模式
    check_address_mode();
    
    // 尝试修复的擦除函数
    printf("\nTesting fixed erase function...\r\n");
    W25QXX_Erase_Sector_Fixed(0);
    
    // 验证擦除结果
    u8 test_data[16];
    W25QXX_Read(test_data, 0, 16);
    
    printf("After erase: ");
    for(int i = 0; i < 16; i++) {
        printf("%02X ", test_data[i]);
    }
    printf("\r\n");
    
    // 检查是否擦除成功
    int erase_ok = 1;
    for(int i = 0; i < 16; i++) {
        if(test_data[i] != 0xFF) {
            erase_ok = 0;
            break;
        }
    }
    
    printf("Erase result: %s\r\n", erase_ok ? "SUCCESS" : "FAILED");
    
    // 如果失败，尝试3字节模式
    if(!erase_ok) {
        printf("\nTrying 3-byte address mode...\r\n");
        force_3byte_mode();
        
        // 再次尝试擦除
        W25QXX_Erase_Sector_Fixed(0);
        
        // 再次验证
        W25QXX_Read(test_data, 0, 16);
        printf("After 3-byte mode erase: ");
        for(int i = 0; i < 16; i++) {
            printf("%02X ", test_data[i]);
        }
        printf("\r\n");
    }
}
void W25QXX_Write_Page_Debug(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);

void W25QXX_Write_NoCheck_Debug(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	
	printf("Write NoCheck: addr=0x%X, size=%u\r\n", WriteAddr, NumByteToWrite);
	
	pageremain = 256 - WriteAddr % 256; // 单页剩余的字节数		 	    
	printf("Page remain: %u\r\n", pageremain);
	
	if(NumByteToWrite <= pageremain) {
		pageremain = NumByteToWrite; // 不大于256个字节
	}
	
	printf("Will write %u bytes\r\n", pageremain);
	
	while(1)
	{	   
		printf("Writing page: addr=0x%X, size=%u\r\n", WriteAddr, pageremain);
		W25QXX_Write_Page_Debug(pBuffer, WriteAddr, pageremain);
		
		if(NumByteToWrite == pageremain) {
			printf("Write complete\r\n");
			break; // 写入结束了
		}
	 	else // NumByteToWrite > pageremain
		{
			printf("Moving to next page\r\n");
			pBuffer += pageremain;
			WriteAddr += pageremain;	
			NumByteToWrite -= pageremain;			  // 减去已经写入了的字节数
			
			printf("Next: addr=0x%X, remaining=%u\r\n", WriteAddr, NumByteToWrite);
			
			if(NumByteToWrite > 256) {
				pageremain = 256; // 一次可以写入256个字节
			} else {
				pageremain = NumByteToWrite; 	  // 不够256个字节了
			}
		}
	}   
}

void W25QXX_Write_Page_Debug(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
	printf("Page write: addr=0x%X, size=%u\r\n", WriteAddr, NumByteToWrite);
	
	// 检查页边界
	u32 page_start = WriteAddr & 0xFFFFFF00;  // 页起始地址
	u32 page_end = page_start + 256;
	u32 write_end = WriteAddr + NumByteToWrite;
	
	if(write_end > page_end) {
		printf("ERROR: Write crosses page boundary! Page end: 0x%X, Write end: 0x%X\r\n", 
		       page_end, write_end);
		return;
	}
	
	// 确保flash不忙
	W25QXX_Wait_Busy();
	
	// 写使能
	W25QXX_Write_Enable();
	
	// 检查写使能状态
	u8 status = W25QXX_ReadSR(1);
	printf("Before page program, status: 0x%02X\r\n", status);
	
	if((status & 0x02) == 0) {
		printf("ERROR: Write enable failed before page program!\r\n");
		return;
	}
	
	// 发送页编程命令
	QSPI_Send_CMD(W25X_PageProgram, WriteAddr, (3<<6)|(3<<4)|(3<<2)|(3<<0), 0);
	QSPI_Transmit(pBuffer, NumByteToWrite);
	
	// 等待写入完成
	printf("Waiting for page program to complete...\r\n");
	W25QXX_Wait_Busy();
	
	// 检查最终状态
	status = W25QXX_ReadSR(1);
	printf("After page program, status: 0x%02X\r\n", status);
}


void test_page_write_simple(void)
{
	printf("=== Simple Page Write Test ===\r\n");
	
	// 准备测试数据
	u8 test_data1[256];
	u8 test_data2[256]; 
	u8 read_data[256];
	
	// 第一页数据：0x00, 0x01, 0x02, ...
	for(int i = 0; i < 256; i++) {
		test_data1[i] = i & 0xFF;
	}
	
	// 第二页数据：0x80, 0x81, 0x82, ...
	for(int i = 0; i < 256; i++) {
		test_data2[i] = (i + 0x80) & 0xFF;
	}
	
	// 擦除扇区
	printf("Erasing sector 0...\r\n");
	W25QXX_Erase_Sector_Fixed(0);
	
	// 写入第一页 (地址 0x000)
	printf("\nWriting first page at 0x000...\r\n");
	W25QXX_Write_Page_Debug(test_data1, 0x000, 256);
	
	// 验证第一页
	W25QXX_Read(read_data, 0x000, 256);
	int errors1 = 0;
	for(int i = 0; i < 256; i++) {
		if(read_data[i] != test_data1[i]) {
			printf("Page 1 error at %d: wrote 0x%02X, read 0x%02X\r\n", 
			       i, test_data1[i], read_data[i]);
			errors1++;
			if(errors1 > 5) break;
		}
	}
	printf("Page 1 result: %s\r\n", errors1 ? "FAILED" : "SUCCESS");
	
	// 写入第二页 (地址 0x100)
	printf("\nWriting second page at 0x100...\r\n");
	W25QXX_Write_Page_Debug(test_data2, 0x100, 256);
	
    delay_ms(1000);
    
	// 验证第二页
	W25QXX_Read(read_data, 0x100, 256);
	int errors2 = 0;
	for(int i = 0; i < 256; i++) {
		if(read_data[i] != test_data2[i]) {
			printf("Page 2 error at %d: wrote 0x%02X, read 0x%02X\r\n", 
			       i, test_data2[i], read_data[i]);
			errors2++;
			if(errors2 > 5) break;
		}
	}
	printf("Page 2 result: %s\r\n", errors2 ? "FAILED" : "SUCCESS");
	
	// 显示前几个字节
	printf("\nFirst 8 bytes of each page:\r\n");
	W25QXX_Read(read_data, 0x000, 8);
	printf("Page 1: ");
	for(int i = 0; i < 8; i++) printf("%02X ", read_data[i]);
	printf("\r\n");
	
	W25QXX_Read(read_data, 0x100, 8);
	printf("Page 2: ");
	for(int i = 0; i < 8; i++) printf("%02X ", read_data[i]);
	printf("\r\n");
}


/* 在tests.c中添加Flash写入测试函数 */
void test_flash_write_read(void)
{
    u8 write_data[512];
    u8 read_data[512];
//    check_protection_status();
//    test_erase_with_address_mode();
		test_page_write_simple();
//    printf("Testing Flash write/read...\r\n");
//    
//    /* 准备测试数据 */
//    for (int i = 0; i < 512; i++) {
//        write_data[i] = i & 0xFF;
//    }
//    
//    /* 擦除扇区0 */
//    printf("Erasing sector 0...\r\n");
//    W25QXX_Erase_Sector(0);
//    
//    /* 验证擦除是否成功 */
//    W25QXX_Read(read_data, 0, 512);
//    int erase_ok = 1;
//    for (int i = 0; i < 512; i++) {
//        if (read_data[i] != 0xFF) {
//            printf("Erase failed at offset %d: 0x%02X\r\n", i, read_data[i]);
//            erase_ok = 0;
//            break;
//        }
//    }
//    
//    if (!erase_ok) {
//        printf("Sector erase failed, aborting test\r\n");
//        return;
//    }
//    
//    printf("Sector erase verified OK\r\n");
//    
//    /* 分段写入测试数据，每次256字节 */
//    printf("Writing test data in 256-byte chunks...\r\n");
//    
//    for (int chunk = 0; chunk < 2; chunk++) {
//        u32 addr = chunk * 256;
//        printf("Writing chunk %d at address 0x%X\r\n", chunk, addr);
//        
//        W25QXX_Write_NoCheck(&write_data[chunk * 256], addr, 256);
//        
//        /* 立即读取验证这个chunk */
//        W25QXX_Read(read_data, addr, 256);
//        
//        for (int i = 0; i < 256; i++) {
//            if (write_data[chunk * 256 + i] != read_data[i]) {
//                printf("Immediate verify failed at chunk %d, offset %d: wrote 0x%02X, read 0x%02X\r\n", 
//                       chunk, i, write_data[chunk * 256 + i], read_data[i]);
//                return;
//            }
//        }
//        printf("Chunk %d verified OK\r\n", chunk);
//    }
//    
//    /* 最终完整读取验证 */
//    printf("Final verification...\r\n");
//    W25QXX_Read(read_data, 0, 512);
//    
//    /* 比较数据 */
//    int errors = 0;
//    for (int i = 0; i < 512; i++) {
//        if (write_data[i] != read_data[i]) {
//            printf("Data mismatch at offset %d: wrote 0x%02X, read 0x%02X\r\n", 
//                   i, write_data[i], read_data[i]);
//            errors++;
//            if (errors > 10) break;
//        }
//    }
//    
//    if (errors == 0) {
//        printf("Flash write/read test PASSED!\r\n");
//    } else {
//        printf("Flash write/read test FAILED with %d errors!\r\n", errors);
//    }
}
