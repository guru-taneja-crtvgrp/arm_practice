#include<LPC214X.h>
void delay(int);
void commands(void);
void data(void);

int cmd[]={0x00000038,0x0000000E,0x00000006,0x00000001,0x00000080};
char dat[]={'G','A','N','J','E',' ','L','U','N',' ','F','A','D',' ','L','E'};

void delay(int amt)
{
	int i,j;
	for (i=0;i<amt;i++)
	for (j=0;j<6000;j++);
}
int main()
{
	IO0DIR |= 0x000007FF;
	commands();
	data();
	return 0;
}
void commands(void)
{
	int i;
	for (i=0;i<5;i++)
	{
		IO0SET = cmd[i];
		IO0CLR = 0x00000300;
		IO0SET |= 0x00000400;
		delay(100);
		IO0CLR |= 0x00000400;
		delay(100);
		IO0CLR = 0x000000FF;
	}
}
void data(void)
{
	int i;
	for (i=0;i<16;i++)
	{
		IO0SET = dat[i];
		IO0SET |= 0x00000100;
		IO0CLR = 0x00000200;
		IO0SET |= 0x00000400;
		delay(100);
		IO0CLR = 0x00000400;
		delay(100);
		IO0CLR = 0x000000FF;
	}
}
