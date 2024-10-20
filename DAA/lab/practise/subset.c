#include <stdio.h>
#include <stdlib.h>

int req, a[10], x[10], n;

void sumofsubsets(int s, int k, int r)
{
    int i;
    static int b=1;
    x[k]=1;
    if(a[k]+s==req){
        printf("\n Subset %d) ",b++);
        for(i=1;i<=k;i++)
            if(x[i]==1)
                printf("%d\t",a[i]);
    }
    else if(a[k]+a[k+1]+s<=req)
        sumofsubsets(a[k]+s,k+1,r-a[k]);
    if((s+r-a[k]>=req)&& (a[k+1]+s)<=req){
        x[k]=0;
        sumofsubsets(s,k+1,r-a[k]);
    }

}

int main()
{
    int i, sum = 0;
    printf("\nEnter the number of elements: ");
    scanf("%d", &n);
    printf("\nEnter the elements in increasing order ");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        sum = sum + a[i];
    }
    printf("\n Enter the required sum: ");
    scanf("%d", &req);
    if(sum<req || a[i]>req)
    {
        printf("\n No possible subsets. ");
        exit(0);
    }
    sumofsubsets(0, 1, sum);
    return 0;
}