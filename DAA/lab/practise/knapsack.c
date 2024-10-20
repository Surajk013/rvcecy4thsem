#include <stdio.h>
#include <stdlib.h>

int n, W, v[10], V[10][10], w[10], x[10];

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void display()
{
    int i, j;
    i = n;
    j = W;
    while (i > 0 || j > 0)
    {
        if (V[i][j] != V[i - 1][j])
        {
            x[i] = 1;
            j = j - w[i];
        }
        i--;
    }
}

int main()
{
    int i, j;
    printf("\nEnter the number of objects: ");
    scanf("%d", &n);
    printf("\nEnter the knapsack capacity: ");
    scanf("%d", &W);
    printf("\nEnter the weights of the objects: ");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
    }
    printf("\nEnter the profits of the objects: ");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &v[i]);
    }
    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= W; j++)
        {
            if (i == 0 || j == 0)
                V[i][j] = 0;
            else
                V[i][j] = (j - w[i] < 0) ? V[i - 1][j] : max(V[i - 1][j], V[i - 1][j - w[i]] + v[i]);
        }
    }
    display();
    printf("\n Max profit: %d", V[n][W]);
    printf("\n Objects included are: ");
    for (i = 0; i <= n; i++)
    {
        if (x[i] == 1)
            printf("\n%d object included", i);
    }
    printf("\n");
    return 0;
}