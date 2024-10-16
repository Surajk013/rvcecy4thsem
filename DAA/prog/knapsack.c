#include <stdio.h>
#include <stdlib.h>

// Function to solve the Knapsack problem using dynamic programming
int knapsack(int W, int wt[], int val[], int n) {
    int i, w;
    int K[n+1][W+1];

    // Build the table K[][] in bottom-up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (wt[i-1] <= w) {
                K[i][w] = (val[i-1] > K[i-1][w-wt[i-1]] + val[i-1]) ? val[i-1] : K[i-1][w-wt[i-1]] + val[i-1];
            } else {
                K[i][w] = K[i-1][w];
            }
        }
    }

    // K[n][W] contains the maximum value that can be obtained
    return K[n][W];
}

int main() {
    int n, W;

    // Input number of items and knapsack capacity
    printf("Enter the number of items: ");
    scanf("%d", &n);

    int *val = (int*)malloc(n * sizeof(int));
    int *wt = (int*)malloc(n * sizeof(int));

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &W);

    // Input values and weights
    printf("Enter the values of the items:\n");
    for (int i = 0; i < n; i++) {
        printf("Value of item %d: ", i + 1);
        scanf("%d", &val[i]);
    }

    printf("Enter the weights of the items:\n");
    for (int i = 0; i < n; i++) {
        printf("Weight of item %d: ", i + 1);
        scanf("%d", &wt[i]);
    }

    // Solve the knapsack problem
    int maxValue = knapsack(W, wt, val, n);
    printf("Maximum value in the knapsack: %d\n", maxValue);

    // Free allocated memory
    free(val);
    free(wt);

    return 0;
}

