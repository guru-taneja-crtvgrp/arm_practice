#include<LPC214X.h>
char rx[5],l=0;
__irq void uart_isr(void)
{
	int iir_value;
	iir_value = U0IIR;
	IO0CLR = 0x00000004;
		VICVectAddr = 0x00;
	//while ( !(iir_value & 0x01) );
//	if( iir_value & 0x00000004 )
//	{
//		rx[l] = U0RBR;
//	}
//	U0THR = rx[l];
//	l++;
	//while( (U0LSR & 0x40) == 0 );
	//memset((void *)U0THR,0,4);

}
void uart_init(void)
{
	PINSEL0 = PINSEL0 | 0x00000005;	/* Enable UART0 Rx0 and Tx0 pins of UART0 */
	U0LCR = 0x83;	                  /* DLAB = 1, 1 stop bit, 8-bit character length */
	U0DLM = 0x00;	                  /* For baud rate of 9600 with Pclk = 12MHz */
	U0DLL = 0x4E;	                  /* We get these values of U0DLL and U0DLM from formula */
	U0LCR = 0x03;                   /* DLAB = 0 */
	U0IER = 0x00000003;	            /* Enable THRE and RBR interrupt */
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
T0MR0=10000000;
T0MCR=0X0006;
	T0TCR=0X01;
while(T0TC<10000000);
T0TCR=0X00;
}
int main(void)
{
	IO0DIR = 0x00000004;
	unsigned char i[] = {'a','b','c','d','e'};
	unsigned int j,k;
	pll_init();
	uart_init();
  interrupt_init();
	for (j=0;j<5;j++)
	{
	    U0THR = i[j];
		  IO0SET = 0x00000004;
		  delay();
	}
	
	//U0THR = i[0];
	while(1);
}
