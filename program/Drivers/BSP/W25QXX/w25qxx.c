#include "./BSP/W25QXX/w25qxx.h"
#include "./BSP/QSPI/qspi.h"

#define printf(fmt, ...) do {} while (0)

//////////////////////////////////////////////////////////////////////////////////	 
							  
////////////////////////////////////////////////////////////////////////////////// 	

u16 W25QXX_TYPE=W25Q64;	//默认是W25Q64
u8 W25QXX_QPI_MODE=0;		//QSPI模式标志:0,SPI模式;1,QPI模式.

//4Kbytes为一个Sector
//16个扇区为1个Block
//W25Q64
//容量为32M字节,共有512个Block,8192个Sector 
													 
//初始化SPI FLASH的IO口
void W25QXX_Init(void)
{ 
    u8 temp;    
    QSPI_Init();                    //初始化QSPI
    W25QXX_Qspi_Enable();          //使能QSPI模式
    W25QXX_TYPE=W25QXX_ReadID();   //读取FLASH ID.
    printf("ID:%x\r\n",W25QXX_TYPE);
    
    if(W25QXX_TYPE==W25Q64)        //SPI FLASH为W25Q64
    {
        temp=W25QXX_ReadSR(3);      //读取状态寄存器3，判断地址模式
        printf("Initial SR3: 0x%02X\r\n", temp);
        
        if((temp&0X01)==1)          //如果是4字节地址模式,则退出4字节地址模式
        { 
            printf("Exiting 4-byte address mode...\r\n");
            W25QXX_Write_Enable();  //写使能
            QSPI_Send_CMD(W25X_Exit4ByteAddr,0,(0<<6)|(0<<4)|(0<<2)|(3<<0),0);//QPI,退出4字节地址指令,地址为0,无数据_8位地址_无地址_4线传输指令,无空周期,0个字节数据 
        }
        
        // 验证是否成功退出4字节模式
        temp=W25QXX_ReadSR(3);
        printf("Address mode status: 0x%02X (%s)\r\n", temp, (temp&0x01) ? "4-byte mode" : "3-byte mode");
        
        // 设置3字节模式下的读参数
        W25QXX_Write_Enable();      //写使能
        QSPI_Send_CMD(W25X_SetReadParam,0,(3<<6)|(0<<4)|(0<<2)|(3<<0),0);  //QPI,设置读参数指令,地址为0,4线传数据_8位地址_无地址_4线传输指令,无空周期,1个字节数据
        temp=3<<4;                  //设置P4&P5=11,8个dummy clocks,104M
        QSPI_Transmit(&temp,1);     //发送1个字节   
    }
}  

//W25QXX进入QSPI模式 
void W25QXX_Qspi_Enable(void)
{
    u8 stareg2;
    stareg2=W25QXX_ReadSR(2);       //先读出状态寄存器2的原始值 
    if((stareg2&0X02)==0)           //QE位未使能
    { 
        W25QXX_Write_Enable();      //写使能 
        stareg2|=1<<1;              //使能QE位		
        W25QXX_Write_SR(2,stareg2); //写状态寄存器2
    }
    QSPI_Send_CMD(W25X_EnterQPIMode,0,(0<<6)|(0<<4)|(0<<2)|(1<<0),0);//写command指令,地址为0,无数据_8位地址_无地址_单线传输指令,无空周期,0个字节数据
    W25QXX_QPI_MODE=1;              //标记QSPI模式
}

//W25QXX退出QSPI模式 
void W25QXX_Qspi_Disable(void)
{ 
    QSPI_Send_CMD(W25X_ExitQPIMode,0,(0<<6)|(0<<4)|(0<<2)|(3<<0),0);//写command指令,地址为0,无数据_8位地址_无地址_4线传输指令,无空周期,0个字节数据
    W25QXX_QPI_MODE=0;              //标记SPI模式
}

//读取W25QXX的状态寄存器，W25QXX一共有3个状态寄存器
//状态寄存器1：
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
//状态寄存器2：
//BIT7  6   5   4   3   2   1   0
//SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
//状态寄存器3：
//BIT7      6    5    4   3   2   1   0
//HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
//regno:状态寄存器号，范:1~3
//返回值:状态寄存器值
u8 W25QXX_ReadSR(u8 regno)   
{  
    u8 byte=0,command=0; 
    switch(regno)
    {
        case 1:
            command=W25X_ReadStatusReg1;    //读状态寄存器1指令
            break;
        case 2:
            command=W25X_ReadStatusReg2;    //读状态寄存器2指令
            break;
        case 3:
            command=W25X_ReadStatusReg3;    //读状态寄存器3指令
            break;
        default:
            command=W25X_ReadStatusReg1;    
            break;
    }   
    if(W25QXX_QPI_MODE)QSPI_Send_CMD(command,0,(3<<6)|(0<<4)|(0<<2)|(3<<0),0);	//QPI,写command指令,地址为0,4线传数据_8位地址_无地址_4线传输指令,无空周期,1个字节数据
    else QSPI_Send_CMD(command,0,(1<<6)|(0<<4)|(0<<2)|(1<<0),0);				//SPI,写command指令,地址为0,单线传数据_8位地址_无地址_单线传输指令,无空周期,1个字节数据
    QSPI_Receive(&byte,1);	        
    return byte;   
}   

//写W25QXX状态寄存器
void W25QXX_Write_SR(u8 regno,u8 sr)   
{   
    u8 command=0;
    switch(regno)
    {
        case 1:
            command=W25X_WriteStatusReg1;    //写状态寄存器1指令
            break;
        case 2:
            command=W25X_WriteStatusReg2;    //写状态寄存器2指令
            break;
        case 3:
            command=W25X_WriteStatusReg3;    //写状态寄存器3指令
            break;
        default:
            command=W25X_WriteStatusReg1;    
            break;
    }   
    if(W25QXX_QPI_MODE)QSPI_Send_CMD(command,0,(3<<6)|(0<<4)|(0<<2)|(3<<0),0);	//QPI,写command指令,地址为0,4线传数据_8位地址_无地址_4线传输指令,无空周期,1个字节数据
    else QSPI_Send_CMD(command,0,(1<<6)|(0<<4)|(0<<2)|(1<<0),0);				//SPI,写command指令,地址为0,单线传数据_8位地址_无地址_单线传输指令,无空周期,1个字节数据
    QSPI_Transmit(&sr,1);	         	      
}  

//W25QXX写使能	
//将S1寄存器的WEL置位   
void W25QXX_Write_Enable(void)   
{
    if(W25QXX_QPI_MODE)QSPI_Send_CMD(W25X_WriteEnable,0,(0<<6)|(0<<4)|(0<<2)|(3<<0),0);	//QPI,写使能指令,地址为0,无数据_8位地址_无地址_4线传输指令,无空周期,0个字节数据
    else QSPI_Send_CMD(W25X_WriteEnable,0,(0<<6)|(0<<4)|(0<<2)|(1<<0),0);				//SPI,写使能指令,地址为0,无数据_8位地址_无地址_单线传输指令,无空周期,0个字节数据
} 

//W25QXX写禁止	
//将WEL清零  
void W25QXX_Write_Disable(void)   
{  
    if(W25QXX_QPI_MODE)QSPI_Send_CMD(W25X_WriteDisable,0,(0<<6)|(0<<4)|(0<<2)|(3<<0),0);//QPI,写禁止指令,地址为0,无数据_8位地址_无地址_4线传输指令,无空周期,0个字节数据
    else QSPI_Send_CMD(W25X_WriteDisable,0,(0<<6)|(0<<4)|(0<<2)|(1<<0),0);				//SPI,写禁止指令,地址为0,无数据_8位地址_无地址_单线传输指令,无空周期,0个字节数据 
} 

//返回值如下:				   
//0XEF13,表示芯片型号为W25Q80  
//0XEF14,表示芯片型号为W25Q16    
//0XEF15,表示芯片型号为W25Q32  
//0XEF16,表示芯片型号为W25Q64 
//0XEF17,表示芯片型号为W25Q128 	  
//0XEF18,表示芯片型号为W25Q256
u16 W25QXX_ReadID(void)
{
    u8 temp[2];
    u16 deviceid;
    if(W25QXX_QPI_MODE)QSPI_Send_CMD(W25X_ManufactDeviceID,0,(3<<6)|(2<<4)|(3<<2)|(3<<0),0);//QPI,读id,地址为0,4线传输数据_24位地址_4线传输地址_4线传输指令,无空周期,2个字节数据
    else QSPI_Send_CMD(W25X_ManufactDeviceID,0,(1<<6)|(2<<4)|(1<<2)|(1<<0),0);			//SPI,读id,地址为0,单线传输数据_24位地址_单线传输地址_单线传输指令,无空周期,2个字节数据
    QSPI_Receive(temp,2);
    deviceid=(temp[0]<<8)|temp[1];
    return deviceid;
}    

//读取SPI FLASH,仅支持QPI模式  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(最大24bit)
//NumByteToRead:要读取的字节数(最大65535)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
    QSPI_Send_CMD(W25X_FastReadData,ReadAddr,(3<<6)|(2<<4)|(3<<2)|(3<<0),8);	//QPI,快速读数据,地址为ReadAddr,4线传输数据_24位地址_4线传输地址_4线传输指令,8空周期,NumByteToRead个数据
    QSPI_Receive(pBuffer,NumByteToRead); 
}  

//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(最大24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
void W25QXX_Write_Page(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
    W25QXX_Write_Enable();                  // 写使能
    
    // 检查写使能是否成功
    u8 status = W25QXX_ReadSR(1);
    if((status & 0x02) == 0) {
        printf("Write enable failed!\r\n");
        return;
    }
    
    QSPI_Send_CMD(W25X_PageProgram, WriteAddr, (3<<6)|(2<<4)|(3<<2)|(3<<0), 0);	//QPI,页写指令,地址为WriteAddr,4线传输数据_24位地址_4线传输地址_4线传输指令,无空周期,NumByteToWrite个数据
    QSPI_Transmit(pBuffer, NumByteToWrite);
    W25QXX_Wait_Busy();                     // 等待写入结束
}

//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(最大24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
    u16 pageremain;	   
    pageremain=256-WriteAddr%256; //单页剩余的字节数		 	    
    if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
    while(1)
    {	   
        W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
        if(NumByteToWrite==pageremain)break;//写入结束了
        else //NumByteToWrite>pageremain
        {
            pBuffer+=pageremain;
            WriteAddr+=pageremain;	

            NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
            if(NumByteToWrite>256)pageremain=256; //一次可以写入256个字节
            else pageremain=NumByteToWrite; 	  //不够256个字节了
        }
    }   
} 

//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(最大24bit)						
//NumByteToWrite:要写入的字节数(最大65535)   
u8 W25QXX_BUFFER[4096];		 
void W25QXX_Write(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)   
{ 
    u32 secpos;
    u16 secoff;
    u16 secremain;	   
    u16 i;    
    u8 * W25QXX_BUF;	  
    
    W25QXX_BUF = W25QXX_BUFFER;	     
    secpos = WriteAddr / 4096;           // 扇区地址  
    secoff = WriteAddr % 4096;           // 在扇区内的偏移
    secremain = 4096 - secoff;           // 扇区剩余空间大小   

    if(NumByteToWrite <= secremain) {
        secremain = NumByteToWrite;      // 不大于4096个字节
    }
    
    while(1) 
    {	
        W25QXX_Read(W25QXX_BUF, secpos * 4096, 4096); // 读出整个扇区的内容
        
        // 校验数据 - 检查要写入的区域是否需要擦除
        for(i = 0; i < secremain; i++)
        {
            if(W25QXX_BUF[secoff + i] != 0XFF) {
                break; // 需要擦除  	  
            }
        }
        
        if(i < secremain) // 需要擦除
        {
            printf("Erasing sector %lu\r\n", secpos);
            W25QXX_Erase_Sector(secpos);        // 擦除这个扇区
            W25QXX_Wait_Busy();                 // 等待擦除完成
            
            // 将新数据复制到缓冲区的对应位置
            for(i = 0; i < secremain; i++)
            {
                W25QXX_BUF[i + secoff] = pBuffer[i];	  
            }
            
            printf("Writing whole sector %lu\r\n", secpos);
            W25QXX_Write_NoCheck(W25QXX_BUF, secpos * 4096, 4096); // 写入整个扇区
            W25QXX_Wait_Busy();                 // 等待写入完成
        }
        else 
        {
            // 写已经擦除了的区域，直接写入扇区剩余区间
            printf("Writing to clean area at 0x%X, size %u\r\n", WriteAddr, secremain);
            W25QXX_Write_NoCheck(pBuffer, WriteAddr, secremain);
            W25QXX_Wait_Busy();                 // 等待写入完成
        }
        
        if(NumByteToWrite == secremain) {
            break; // 写入结束了
        }
        else // 写入未结束
        {
            secpos++;                           // 扇区地址增1
            secoff = 0;                         // 偏移位置为0 	 

            pBuffer += secremain;               // 指针偏移
            WriteAddr += secremain;             // 写地址偏移	   
            NumByteToWrite -= secremain;        // 字节数递减
            
            if(NumByteToWrite > 4096) {
                secremain = 4096;               // 下一个扇区还是写不完
            }
            else {
                secremain = NumByteToWrite;     // 下一个扇区可以写完了
            }
        }	 
    };	 
}

//擦除整个芯片		  
//等待时间超长...
void W25QXX_Erase_Chip(void)   
{                                   
    W25QXX_Write_Enable();					//SET WEL 
    W25QXX_Wait_Busy();   
    QSPI_Send_CMD(W25X_ChipErase,0,(0<<6)|(0<<4)|(0<<2)|(3<<0),0);//QPI,写全片擦除指令,地址为0,无数据_8位地址_无地址_4线传输指令,无空周期,0个字节数据
    W25QXX_Wait_Busy();						//等待芯片擦除结束
} 

//擦除一个扇区
//Dst_Addr:扇区地址 根据实际容量设置
//擦除一个扇区的最少时间:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)   
{  
    u32 sector_addr = Dst_Addr * 4096;
    
    printf("Erasing sector %lu, address 0x%08lX\r\n", Dst_Addr, sector_addr);
    
    // 检查初始状态
    u8 status = W25QXX_ReadSR(1);
    printf("Initial status: 0x%02X\r\n", status);
    
    // 写使能
    W25QXX_Write_Enable();
    
    // 检查写使能是否成功
    status = W25QXX_ReadSR(1);
    printf("After write enable, status: 0x%02X\r\n", status);
    
    if((status & 0x02) == 0) {
        printf("ERROR: Write enable failed!\r\n");
        return;
    }
    
    // 等待不忙
    W25QXX_Wait_Busy();
    
    // 发送擦除命令 - 使用24位地址
    printf("Sending sector erase command...\r\n");
    QSPI_Send_CMD(W25X_SectorErase, sector_addr, (0<<6)|(2<<4)|(3<<2)|(3<<0), 0);	//QPI,写扇区擦除指令,地址为sector_addr,无数据_24位地址_4线传输地址_4线传输指令,无空周期,0个字节数据
    
    // 等待擦除完成
    printf("Waiting for erase to complete...\r\n");
    W25QXX_Wait_Busy();
    
    // 检查最终状态
    status = W25QXX_ReadSR(1);
    printf("After erase, status: 0x%02X\r\n", status);
}

//等待空闲
void W25QXX_Wait_Busy(void)   
{   
    while((W25QXX_ReadSR(1) & 0x01) == 0x01)  // BUSY位为1时继续等待
    {
        // 添加小延时，避免过于频繁地读取状态寄存器
        HAL_Delay(1);  // 使用系统延时函数更可靠
    }
}
