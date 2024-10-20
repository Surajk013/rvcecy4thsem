#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10 // Maximum number of nodes

// Function to return the minimum of two values
int min(int a, int b)
{
    if (a < b)
        return a; // Return a if it's less than b
    else
        return b; // Otherwise, return b
}

// Function implementing the Floyd-Warshall algorithm
void Floyds(int D[MAX_NODES][MAX_NODES], int n)
{
    int i, j, k;

    // Triple nested loop to update the distance matrix
    for (k = 1; k <= n; k++) // Intermediate node loop
    {
        for (i = 1; i <= n; i++) // Source node loop
        {
            for (j = 1; j <= n; j++) // Destination node loop
            {
                // Update D[i][j] with the minimum distance found
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]); // Correct formula
            }
        }
    }
}

int main()
{
    int n, i, j, D[MAX_NODES][MAX_NODES]; // Initialize variables

    // Read the number of nodes in the graph
    printf("Read the number of nodes: ");
    scanf("%d", &n);

    // Read the weighted adjacency matrix
    printf("Read the weighted matrix:\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            scanf("%d", &D[i][j]); // Input for adjacency matrix
        }
    }

    // Apply Floyd-Warshall algorithm to find all-pairs shortest paths
    Floyds(D, n);

    // Output the resulting all-pairs shortest path matrix
    printf("The all-pair shortest path matrix is:\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            printf("%d ", D[i][j]); // Print the distance from i to j
        }
        printf("\n"); // Newline after each row
    }

    return 0; // Exit the program
}
