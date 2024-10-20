#include<stdio.h>
#include<stdlib.h>
int count =0 ;
#define MAX 550

void swap(int *a, int *b){
    int t  = *a;
    *a=*b;
    *b = t;
}

int partition(int a[MAX],int left, int right){
    int i,j, pivot;
    pivot = a[left];
    i= left+1;
    j= right;
    while(1){
        count++;
        while(pivot>=a[i] && i<=right)
            i++;
        while(pivot<a[j])
            j--;
        if(i<j){
            swap(&a[i],&a[j]);

        }
        else{
            swap(&a[left],&a[j]);
            return j;
        }
    }
}

void quicksort(int a[MAX], int left, int right){
    int s;
    if(left<right){
        s = partition(a,left,right);
        quicksort(a,left,s-1);
        quicksort(a,s+1,right);
    }
}

int main(){
    int n,a[MAX];
    printf("\nEnter no. of elements in the array: ");
    scanf("%d", &n);
    printf("\nEnter the elements of the array: ");
    for(int i=0;i<n;i++)
        scanf("%d", &a[i]);

    quicksort(a,0,n-1);

    printf("\nElements in the array after sorting: ");
    for(int i=0;i<n;i++)
        printf("%d ", a[i]);

    printf("\nCount :",count);

    int c1,c2,c3;
    int b[MAX],c[MAX];

    printf("\nSIZE \t ASC \t DESC \t RAND\n");

    for(int i=16;i<550;i=i*2){
        for(int j=0;j<i;j++){
            a[j] = j;
            b[j] = i-j;
            c[j] = rand()%i;
        }

        count = 0;
        quicksort(a,0,i-1);
        c1 = count;

        count = 0;
        quicksort(b,0,i-1);
        c2 = count;

        count = 0;
        quicksort(c,0,i-1);
        c3 = count;

        printf("%d \t %d \t %d \t %d\n",i,c1,c2,c3);
    }

    return 0;
}