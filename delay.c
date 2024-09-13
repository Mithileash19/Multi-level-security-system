#include <LPC21xx.H>

void delay_ms(unsigned int ms){
	T0PR=60000-1;
	T0TC=T0PC=0;
	T0TCR=0x1;
	while(T0TC<ms);
	T0TCR=0x0;
}

