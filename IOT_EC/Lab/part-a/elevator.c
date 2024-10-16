#include<lpc214x.h>
#define ledon (IO0CLR = 1U << 31)
#define ledoff (IO0SET = 1U << 31)
#define PLOCK 0X00000400

void delayms(unsigned int j);
void elevatorrun();
int  main(){
	IO0DIR |= 1U << 31 | 0XFF << 16;
	IO1DIR |= 1 << 24;
	ledon;
	elevatorrun();
}

void elevatorrun(void){
	int i,val=0;
	unsigned int counter;
	IO1CLR = 1 << 24;
	IO0CLR = 0X000F0000;
	do{
		IO0CLR=0X00F00000;IO0SET=0X00F00000;
		do{
			counter = (IO1PIN >> 16)& 0X0000000F;
		}while(counter == 0X0F);
		if(counter == 0X0E) val=3;
		else if(counter == 0X0D) val=6;
		else if(counter == 0X0B) val=8;
		else if(counter == 0X07) val=10;
		
		for (i=0;i<val;i++){
			IO0DIR=0X000F0000; IO0SET= 1 << 16;
			delayms(250);
		}
		for (i=val-1;i>=0;i--){
			IO0DIR=0X000F0000; IO0SET= 1 << 16;
			delayms(250);
		}
	}
	while(1);
}



void delayms(unsigned int j){
	unsigned int i,x;
	for(i=0;i<j;i++){
		for(x=0;x<10000;x++);
	}
}