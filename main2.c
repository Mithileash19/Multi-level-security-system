#include <LPC21xx.h>
#include "types.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "delay.h"
#include <string.h>
#include "keypad.c"
#include "lcd.h"
#include "dc_motor.c"
#include "uart.h"
#include "gsm_module.c"
#define SW	15


#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr

#define gLED 1<<16 //P1.16
#define rLED 1<<17 //P1.17

u8 p[9] __attribute__((at(0x40000040)))="";

void INIT_DISPLAY(void)
{
	LCD_COMMAND(0XC0);
	LCD_STR("V23CE6S2");
	LCD_COMMAND(0X80);
	LCD_STR("MULTI LEVEL SECURIY SYSTEM");
	delay_ms(500);
}
void EXIT_DISPLAY(void)
{
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("VISIT AGAIN");
	LCD_COMMAND(0XC0);
	LCD_STR("THANK YOU");
}
	
int main()
{
	u8 ch,i=0;
	u8 rx[9];//,otp[20];
//	u8 r_otp[20];
	int r_otp = 0; 
	u32 x,count;
	init_i2c();
	LCD_INIT();

	UART0_INIT();
	INIT_DISPLAY();
	while(1)
	{
		if(((IOPIN0>>SW)&1) == 0)
			break;
		LCD_COMMAND(0X01);
		LCD_COMMAND(0X80);
		LCD_STR("PRESS SWITCH");
	}
// i2c_eeprom_write(0X50,0X00,'A');
// ch=i2c_eeprom_read(0X50,0X00);");

	while(1)
	{
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("ENTER PASSWORD");
	LCD_COMMAND(0XC0);
	i=0;
	while(i != 6)//ascii value for '\r'
	{
			ch = key_scan();
			LCD_DATA('*');
			rx[i++] = ch+48;
	}
	rx[6]='\0';
	i2c_eeprom_page_write(I2C_EEPROM_SA,0x00,"123456",6);
	i2c_eeprom_seq_read(I2C_EEPROM_SA,0x00,p,6);
	p[8] = '\0';
	delay_ms(100);
	if(strcmp(p,rx)==0)
	//if(ch=='A')
	{
	
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("PASSWORD MATCHED");
	LCD_COMMAND(0X80);
	LCD_STR("OTP GENERATING...");
	delay_ms(500);
	x = message_sender();
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("ENTER OTP");
	i=0;
	LCD_COMMAND(0XC0);	
	while(i++ < 4)//ascii value for '\r'
	{
		ch = key_scan();
		LCD_DATA('*');
//		r_otp[i++] = ch+48;
		r_otp = (r_otp*10) + ch;
		
	}
//	LCD_INTEGER(r_otp);	
//	delay_ms(500);		
//	r_otp[4] = '\0';
//	for(i=0;i>=3;i++,x/10)
//		otp[i] = (x%10)+48;
//	otp[4] = '\0';
	if (x == r_otp)
	{
		door_open();
		EXIT_DISPLAY();
		return 0;
	}
	}
		
	else
	{
					++count;
					LCD_COMMAND(0XC0);
					LCD_STR("PASSWORD INVALID");
					delay_ms(1000);
					if(count == 3)
					{
						LCD_COMMAND(0X01);
						LCD_COMMAND(0X80);
						LCD_STR("SYSTEM BLOCKED");
						delay_ms(1000);
						EXIT_DISPLAY();
						return 0;
					}
	}
	}
}



