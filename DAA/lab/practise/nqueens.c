#include<stdio.h>
#include<stdlib.h>
int c=1;
int x[10];

void printboard(int n){
    int i,j;
    printf("\nSolution %d: ",c++);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(x[i]==j)
                printf("Q\t");
            else
                printf("-\t");
        }
        printf("\n");
    }
}

int place(int k,int i){
    int j;
    for(j=1;j<k;j++){
        if(x[j]== i || abs(x[j]-i)==abs(j-k))
            return 0;
    }
    return 1;
}

void nqueens(int k,int n){
    int i;
    for(i=1;i<=n;i++){
        if(place(k,i)){
            x[k]=i;
            if(k==n){
                printf("\n");
                printboard(n);
            }
            else
                nqueens(k+1,n);
        }
    }
}

int main(){
    int n;
    printf("\nEnter the number of queeens: ");
    scanf("%d",&n);
    nqueens(1,n);
    if(c==1)
        printf("\nNo possible solutions");
}