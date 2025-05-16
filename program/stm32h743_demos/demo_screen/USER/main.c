#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"


int main(void)
{	 
    u8 x=0;
  	u8 lcd_id[12];
	
	Cache_Enable();                			//��L1-Cache
	HAL_Init();				        		//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);  		    //����ʱ��,400Mhz 
	delay_init(400);						//��ʱ��ʼ��
	uart_init(115200);						//���ڳ�ʼ��
	LED_Init();								//��ʼ��LED
	KEY_Init();								//��ʼ������
	SDRAM_Init();                   		//��ʼ��SDRAM
    LCD_Init();                     		//��ʼ��LCD
	POINT_COLOR=RED; 
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣	
    while(1)
    {
        switch(x)
				{
					case 0:LCD_Clear(WHITE);break;
					case 1:LCD_Clear(BLACK);break;
					case 2:LCD_Clear(BLUE);break;
					case 3:LCD_Clear(RED);break;
					case 4:LCD_Clear(MAGENTA);break;
					case 5:LCD_Clear(GREEN);break;
					case 6:LCD_Clear(CYAN);break; 
					case 7:LCD_Clear(YELLOW);break;
					case 8:LCD_Clear(BRRED);break;
					case 9:LCD_Clear(GRAY);break;
					case 10:LCD_Clear(LGRAY);break;
					case 11:LCD_Clear(BROWN);break;
				}
				POINT_COLOR=RED;	  
			LCD_ShowString(10,40,240,32,32,"STM32H743"); 	
		LCD_ShowString(10,80,240,24,24,"LTDC LCD TEST");					 
					x++;
				if(x==12)x=0;      
				LED0_Toggle; 
				delay_ms(1000);	
	}
}

