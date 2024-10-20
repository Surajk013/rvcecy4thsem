#include <stdio.h>
#include <stdlib.h>
int w[10]; // denotes set s
int x[10]; // boolean array which tells if ele is part of subset or not
int d;     // max value recieves when ele is added in the subset
void sumSubset(int s, int k, int r)
{
    int i;
    static int b = 1; // number of subsets
    x[k] = 1;
    if (w[k] + s == d)
    {
        printf("\nSubset %d) ", b++);
        for (i = 1; i <= k; i++)
            if (x[i] == 1)
                printf("%d\t", w[i]);
    }
    else if (s + w[k] + w[k + 1] <= d)
        sumSubset(s + w[k], k + 1, r - w[k]);
    if ((s + r - w[k] >= d) && (s + w[k + 1] <= d))
    {
        x[k] = 0;
        sumSubset(s, k + 1, r - w[k]);
    }
}
int main()
{
    int n, i, sum = 0;
    printf("\nSUBSET PROBLEM\n");
    printf("\nEnter the number of elements - ");
    scanf("%d", &n);
    printf("\nEnter the elements (in increasing order) - ");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
        sum += w[i];
    }
    printf("\nEnter the subset max value required - ");
    scanf("%d", &d);
    if (sum < d || w[1] > d)
    {
        printf("\nNo subsets possible!!\n");
        exit(0);
    }
    sumSubset(0, 1, sum);
    // 0-s 1-k sum-r
    return (0);
}