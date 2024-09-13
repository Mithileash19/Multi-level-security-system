#include <LPC21XX.H>
#define input1 1<<4
#define input2 1<<5
void door_open(void)
{
	IODIR0 |= input1|input2;
	IOCLR0 = input1|input2;
	delay_ms(1000);
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("DOOR UNLOCKED");
	IOSET0 = input1;
	IOCLR0 = input2;
	delay_ms(1000);
	LCD_COMMAND(0X80);
	LCD_STR("DOOR LOCKED");
	IOSET0 = input2;
	IOCLR0 = input1;
	delay_ms(1000);
	IOCLR0 = input1|input2;
}
