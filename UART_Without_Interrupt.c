#include<LPC214X.h>
void uart_init(void)
{
	PINSEL0 = PINSEL0 | 0x00000005;	/* Enable UART0 Rx0 and Tx0 pins of UART0 */
	U0LCR = 0x83;	                  /* DLAB = 1, 1 stop bit, 8-bit character length */
	U0DLM = 0x00;	                  /* For baud rate of 9600 with Pclk = 12MHz */
	U0DLL = 0x4E;	                  /* We get these values of U0DLL and U0DLM from formula */
	U0LCR = 0x03;                   /* DLAB = 0 */
	//U0IER = 0x00000003;	            /* Enable THRE and RBR interrupt */
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
	U0THR = 'A';
	while( (U0LSR & 0x40) == 0 );
	U0THR = 'B';
	while( (U0LSR & 0x40) == 0 );
	U0THR = 'C';
	while( (U0LSR & 0x40) == 0 );
	while(1);
}
