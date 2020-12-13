#include<lpc214x.h>
#define TRUE 1
#define FALSE 0
void timer_init(void);
void interrupt_init(void);
void delay(void);
unsigned int ON=FALSE;
int i,j=512;
void led_barISR(void) __irq
{
	T0TCR = 0x00;
	if (ON == FALSE)
	{
		for (i=0;i<10;i++)
		{
			IO0SET |= (1<<i);
			delay();
		}
		//IOSET0 = 0x00000001;
		ON = TRUE;
	}
	else
	{
		for(i=0;i<10;i++)
		{
			IO0CLR |= (j>>i);
			delay();
		}
		//IOCLR0 = 0x00000001;
		ON = FALSE;
	}
	VICVectAddr = 0x00;
	T0IR = 1;
	T0TCR = 0x01;
}
int main()
{
	IODIR0 = 0x0000FFFF;
	timer_init();
	interrupt_init();
	T0TCR = 0x01;
	while(1);
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
void delay(void)
{
	T1CTCR = 0x00;
	T1MCR = 0x06;
	T1MR0 = 500;
	T1PR = 11999;
	T1TCR = 0x02;
	T1TCR = 0x01;
	while(T1TCR);
}
void interrupt_init(void)
{
	VICIntSelect = 0;    //Setting Interrupt type as IRQ, setting this as 1 will set interrupt type as FIQ
	VICIntEnable = 16;
	VICVectCntl0 = 36;
	VICVectAddr0 = (unsigned int)led_barISR;
}
