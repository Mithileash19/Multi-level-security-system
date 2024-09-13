#include <LPC21XX.H>
#define sw 15
int random_otp_generator(void);
int message_sender()
{
		int otp;
		otp = random_otp_generator();	
		UART0_STR("AT\r\n");
		delay_ms(500);
		UART0_STR("AT+CMGF=1;\r\n");
		delay_ms(500);
		UART0_STR("AT+CMGS=\"+916379368823\"\r\n");
		delay_ms(500);
		UART0_STR("OTP:");
		delay_ms(500);
		UART0_INT(otp); 
		UART0_TX(0X1A);
		return otp;
}
int random_otp_generator(void)
{
	unsigned int i;
	while(1)
	{
		for(i=1000;i<=9999;i++)
		{
				if(i == 9999)
					i = 1000;
				if(((IOPIN0>>sw)&1) == 0)
				return i;
		}
	}
}



	




