#include<lpc214x.h>
#define ledon (IO0CLR = 1U << 31)
#define ledoff (IO0SET = 1U << 31)
#define PLOCK 0X00000400

void delayms(unsigned int j);
unsigned char getalphacode(unsigned char data);
void alphadisp(char *buf);

unsigned char getalphacode(unsigned char data){
	switch(data){
		case 'p':return 0X8c;
		default:break;
	}
	return 0xff;
}


void alphadisp(char *buf){
	unsigned char i,j;
	unsigned char seg7data,temp;
	for(i=0;i<5;i++){
		seg7data = getalphacode(*(buf+i));
		for(j=0;j<8;j++){
				temp=seg7data & 0X80;
			if(temp ==0X80 )
					IOSET0 |= 1 << 19;
			else
				IOCLR0 	 |= 1 << 19;
			IOSET0 |= 1 << 20;
			delayms(250);
			IOCLR0 |= 1 << 20;
			seg7data=seg7data << 1 ;
		}
	}
	IOSET0 |= 1 << 30;
	delayms(250);
	IOSET0 |= 1 << 30;
	return ;
}

int main(){

	IO0DIR |= 1U << 31 | 1U << 30 | 1U << 19 | 1U << 20;
	ledon;
	while(1){
		alphadisp("fire");
		delayms(250);
		alphadisp("help");
		delayms(250);
	}
}




void delayms(unsigned int j){
	unsigned int i,x;
	for(i=0;i<j;i++){
		for(x=0;x<10000;x++);
	}
}