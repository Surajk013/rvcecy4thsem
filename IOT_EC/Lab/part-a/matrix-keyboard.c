#include<lpc214x.h>
#include<stdio.h>
#define ledon (IO0CLR = 1U << 31)
#define ledoff (IO0SET = 1U << 31)
#define PLOCK 0X00000400
#define COL0 (IO1PIN & (1 << 19))
#define COL1 (IO1PIN & (1 << 18))
#define COL2 (IO1PIN & (1 << 17))
#define COL3 (IO1PIN & (1 << 16))


void delayms(unsigned int j);
void uart_init(void);
unsigned char lookup_table[4][4]={
	{'0','1','2','3'},
	{'4','5','6','7',},
		{'8','9','a','b'},
			{'c','d','e','f'},

};

unsigned char rowsel=0,colsel=0;




int main(){
	
	uart_init();
	IO0DIR = 1U << 31 | 0X00FF0000;
	ledon;delayms(500);ledoff;
	do{
		while(1){
			rowsel=0;IO0CLR=0X000F0000;IO0SET= 1 << 16;
			if(COL0==0){colsel=0;break;};if(COL1==0){colsel=1;break;};
			if(COL2==0){colsel=2;break;};if(COL3==0){colsel=3;break;};
			rowsel=1;IO0CLR=0X000F0000;IO0SET= 1 << 17;
			if(COL0==0){colsel=0;break;};if(COL1==0){colsel=1;break;};
			if(COL2==0){colsel=2;break;};if(COL3==0){colsel=3;break;};
			rowsel=2;IO0CLR=0X000F0000;IO0SET= 1 << 18;
			if(COL0==0){colsel=0;break;};if(COL1==0){colsel=1;break;};
			if(COL2==0){colsel=2;break;};if(COL3==0){colsel=3;break;};
			rowsel=3;IO0CLR=0X000F0000;IO0SET= 1 << 19;
			if(COL0==0){colsel=0;break;};if(COL1==0){colsel=1;break;};
			if(COL2==0){colsel=2;break;};if(COL3==0){colsel=3;break;};
		}
		delayms(50);
		while(COL0==0 || COL1==0 || COL2==0 || COL3==0)
		delayms(50);
		IO0SET=0X000F0000;
		U0THR=lookup_table[rowsel][colsel];
	}
	while(1);
}


void uart_init(void){

	PINSEL0 |= 0X00000005;
	U0LCR=0X83;
	U0DLM=0;U0DLL=8;
	U0LCR=0X03;
	U0FCR=0X07;

}


void delayms(unsigned int j){
	unsigned int i,x;
	for(i=0;i<j;i++){
		for(x=0;x<10000;x++);
	}
}