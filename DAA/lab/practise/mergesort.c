#include<stdio.h>
#include<stdlib.h>
#define size 1025

int count =0;

void merge(int a[size],int l,int m,int r){
	int i,j,k,b[size];
	i=l;
	j=m+1;
	k=l;
	while(i<=m && j<=r){
		if(a[i]<=a[j]){
			b[k++]=a[i++];
			count++;
		}
		else{
			b[k++]=a[j++];
			count++;
		}
	}
	while(i<=m)
		b[k++]=a[i++];
	while(j<=r)
		b[k++]=a[j++];
	for(i=l;i<k;i++)
		a[i]=b[i];
}

void mergesort(int a[size],int l,int r){
	if(l<r){
		int m=l+(r-l)/2;
		mergesort(a,l,m);
		mergesort(a,m+1,r);
		merge(a,l,m,r);
	}
}

int main(){
	int a[size],x[size],y[size],z[size];
	int i,j,n,c1,c2,c3;
	printf("\n Enter the number of elements: ");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("\n Enter element %d: ",i+1);
		scanf("%d",&a[i]);
	}
	mergesort(a,0,n-1);
	printf("\n Sorted array is: ");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);

	printf("\n Count: %d",count);

	printf("\nSIZE\tASC\tDESC\tRAND");
	for(i=16;i<size;i*=2){
		for(j=0;j<i;j++){
			x[j]=j;
			y[j]=i-j-1;
			z[j]=rand()%i;
		}
		count=0;
		mergesort(x,0,i-1);
		c1=count;
		count=0;
		mergesort(y,0,i-1);
		c2=count;
		count=0;
		mergesort(z,0,i-1);
		c3=count;
		printf("\n%d\t%d\t%d\t%d",i,c1,c2,c3);
	}
	return 0;
}
