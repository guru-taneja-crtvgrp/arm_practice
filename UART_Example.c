#include<LPC214X.h>
char rx[10];
unsigned int l;
void uart_init(void)
{
	PINSEL0 = PINSEL0 | 0x00000005;	/* Enable UART0 Rx0 and Tx0 pins of UART0 */
	U0LCR = 0x83;	                  /* DLAB = 1, 1 stop bit, 8-bit character length */
	U0DLM = 0x00;	                  /* For baud rate of 9600 with Pclk = 12MHz */
	U0DLL = 0x4E;	                  /* We get these values of U0DLL and U0DLM from formula */
	U0LCR = 0x03;  
  U0TER = 0x80;   	/* DLAB = 0 */
	U0IER = 0x00000003;	            /* Enable THRE and RBR interrupt */
}
void delay()
{
T0TCR=0X02;
T0CTCR=0X00;
T0PR=0X1D;
T0MR0=500000;
T0MCR=0X0006;
	T0TCR=0X01;
while(T0TC<500000);
T0TCR=0X00;
}
__irq void uart_isr(void)
{
   
	int iir_value;
  iir_value = U0IIR;
	if( iir_value & 0x00000004 )
	{
		rx[l] = U0RBR;
		U0THR = rx[l];
	}
      l++;
	   //U0IIR=0x01;
	iir_value = U0IIR;
	if(iir_value==0X03)
	{
		IO0CLR=(1<<15);
	}
	VICVectAddr = 0x00;
	
}
void interrupt_init(void)
{
	VICVectAddr0 = (unsigned) uart_isr;	/* UART0 ISR Address */
	VICVectCntl0 = 0x00000026;	/* Enable UART0 IRQ slot */
	VICIntEnable = 0x00000040;	/* Enable UART0 interrupt */
	VICIntSelect = 0x00000000;	/* UART0 configured as IRQ */
}

void pll_init(void)
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
void delay()
{
T0TCR=0X02;
T0CTCR=0X00;
T0PR=0X1D;
T0MR0=500000;
T0MCR=0X0006;
	T0TCR=0X01;
while(T0TC<500000);
T0TCR=0X00;
}
int main(void)
{
	IO0DIR=0X0000FF00;
	IO0SET=(1<<15);
	pll_init();
	uart_init();
  interrupt_init();
	U0THR = 'b';

		U0THR = 'b';

		U0THR = 'c';

		U0THR = 'd';
	
		U0THR = 'e';
	while(1);
}
