#include<lpc214x.h>
#define ledon (IO0CLR = 1U << 31)
#define ledoff (IO0SET = 1U << 31)
#define PLOCK 0X00000400

void delayms(unsigned int j);

int main(){

	unsigned int clk_steps=100,aclk_steps=100;
	IO0DIR |= 1U << 31 | 1U << 30 | 0X00FF0000;
	ledon;
	do{
			IO0CLR=0X000F0000;IO0SET=0x00010000;delayms(10);if(--clk_steps==0)break;
			IO0CLR=0X000F0000;IO0SET=0x00020000;delayms(10);if(--clk_steps==0)break;
			IO0CLR=0X000F0000;IO0SET=0x00040000;delayms(10);if(--clk_steps==0)break;
			IO0CLR=0X000F0000;IO0SET=0x00080000;delayms(10);if(--clk_steps==0)break;
		}while(1);
	do{		
			IO0CLR=0X000F0000;IO0SET=0x00080000;delayms(10);if(--clk_steps==0)break;
			IO0CLR=0X000F0000;IO0SET=0x00040000;delayms(10);if(--clk_steps==0)break;
			IO0CLR=0X000F0000;IO0SET=0x00020000;delayms(10);if(--clk_steps==0)break;
			IO0CLR=0X000F0000;IO0SET=0x00010000;delayms(10);if(--clk_steps==0)break;
	}while(1);
	IO0CLR=0X00FF0000;
	while(1);
}


void delayms(unsigned int j){
	unsigned int i,x;
	for(i=0;i<j;i++){
		for(x=0;x<10000;x++);
	}
}