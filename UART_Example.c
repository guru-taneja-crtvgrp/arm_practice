#include<LPC214X.h>
char rx;
__irq void uart_isr(void)
{
	//while( (U0LSR & 0x40) == 0 );
	VICVectAddr = 0x00;
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
	VICIntSelect = 0x00000000;	        /* UART0 configured as IRQ */
	VICIntEnable = 0x00000040;	        /* Enable UART0 interrupt */
	VICVectCntl0 = 0x00000026;	        /* Enable UART0 IRQ slot */
	VICVectAddr0 = (unsigned) uart_isr;	/* UART0 ISR Address */
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
int main(void)
{
	pll_init();
	uart_init();
  //interrupt_init();
	U0THR = 'A';
	while(1);
}
