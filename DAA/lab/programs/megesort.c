#include <stdio.h>
#include <stdlib.h>
#define size 1025 // to print for sizes till 1024
int count = 0;

void merge(int a[size], int l, int m, int r)
{
    int i, j, k; // iterators
    i = l;       
    j = m + 1;
    k = l;
    int b[size];
    while (i <= m && j <= r)
    {
        if (a[i] < a[j])
        { // the elements of the first part of the array are lesser than the elements of the second part of array
            b[k++] = a[i++];
            count++;
        }
        else
        { // if the second part of the array have elements that are lesser than the elements of the first part
            b[k++] = a[j++];
            count++;
        }
    }

    while (i <= m)
    { // remainders of the first part of array
        b[k++] = a[i++];
    }
    while (j <= r)
    { // the remainders of the second part of array
        b[k++] = a[j++];
    }
    for (i = l; i < k; i++) // copy back to the main array
        a[i] = b[i];
}

void mergesort(int a[size], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergesort(a, l, m);
        mergesort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main()
{
    int a[size], x[size], y[size], z[size];
    int n, i, j, c1, c2, c3;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    printf("Read array alements");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    mergesort(a, 0, n - 1);
    printf("\nsorted array: ");
    for (i = 0; i < n; i++)
        printf("%d\t", a[i]);
    printf("\nCount = %d \n", count);

    // generating random orders of elements to calculate time complexity of mergesort
    printf("\nSIZE\tASC\tDESC\tRAND\n");
    for (i = 16; i < size; i *= 2)
    {
        for (j = 0; j < i; j++)
        {
            x[j] = j;
            y[j] = i - j - 1;
            z[j] = rand() % i;
        }
        count = 0;
        mergesort(x, 0, i - 1);
        c1 = count;
        count = 0;
        mergesort(y, 0, i - 1);
        c2 = count;
        count = 0;
        mergesort(z, 0, i - 1);
        c3 = count;
        printf("%d\t%d\t%d\t%d\n", i, c1, c2, c3);
    }
}