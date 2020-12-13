#include<lpc214x.h>
void timer_init(void);
void interrupt_init(void);
unsigned int flag=0;
void timerISR(void) __irq
{
	T0TCR = 0x00;				 //Reset Timer
	if (flag == 0)
	{
		IOSET0 = 0x00000001;
		flag = 1;
	}
	else
	{
		IOCLR0 = 0x00000001;
		flag = 0;
	}
	VICVectAddr = 0x00;
  T0TCR = 0x01;				 //Start Timer
	T0IR = 1;
}
int main()
{
	IO0DIR = 0x0000FFFF;
	timer_init();
	interrupt_init();
	T0TCR = 0x01;        //Enable Timer
	while(1);
}
void interrupt_init(void)
{
	VICIntSelect = 0;
	VICIntEnable = 16;
	VICVectCntl0 = 36;
	VICVectAddr0 = (unsigned)timerISR; // Pointer for the ISR
}
void timer_init(void)
{
		VPBDIV = 0x01;
	  T0TCR = 0x02;				 //Reset Timer
		T0CTCR = 0x00;   //Set Timer 0 into Timer Mode 
	  T0PR = 11999; 			 //Value to make delay of 1ms
	  T0MCR = 0x03;				 //Tell processor to reset timer after 1 sec
		T0MR0 = 1000;        //Value to make delay of 1sec 
}
