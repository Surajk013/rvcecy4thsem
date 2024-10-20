#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 256

int table[size];

void shifttable(char p[10]){
	int i,m;
	m=strlen(p);
	for(i=0;i<size;i++)
		table[i]=m;
	for(i=0;i<m-2;i++)
		table[p[i]]=m-i-1;
}

int horspool(char t[size],char p[10]){
	int i,j,m,n,k;
	m=strlen(p);
	n=strlen(t);
	shifttable(p);
	i=m-1;
	while(i<n){
		k=0;
		while(k<m && p[m-k-1]==t[i-k])
			k++;
		if(k==m)
			return i-m+2;
		else
			i=i+table[t[i]];
	}
	return -1;
}

int main(){
		char t[size],p[10];
		int flag;
		printf("\n Enter the text: ");
		scanf("%s", t);
		printf("\n Enter the pattern: ");
		scanf("%s", p);
		flag=horspool(t,p);
		if(flag==-1)
			printf("\n The pattern is not found in the text.");
		else
			printf("\n Pattern is found at index %d ",flag);
}