#include<lpc214x.h>
void delay(void);
void timer_init(void);
int main()
{
	IO0DIR = 0x0000FFFF;
	timer_init();
		while(1)
		{
		IOSET0 = 0x00000001;
	delay();
		IOCLR0 = 0x00000001;
	delay();
		}
}
void timer_init(void)
{
	PLL0CON = 0x01;
	PLL0CFG = 0x60;
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	while(!(PLL0STAT & 0x00000400));
	PLL0CON = 0x03;
		PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
			VPBDIV = 0x01;
}
void delay(void)
{

	  T0TCR = 0x02;				 //Reset Timer
		T0CTCR = 0x00;   //Set Timer 0 into Timer Mode 
	  T0PR = 11999; 			 //Value to make delay of 1ms
	  T0MCR = 0x06;				 //Tell processo r to reset timer after 1 sec
		T0MR0 = 1000;        //Value to make delay of 1sec 
	  T0TCR = 0x01;
	while(T0TCR);
	T0TCR = 0x00;
}
