#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to perform DFS and topological sorting
void topologicalSortUtil(int v, int** adj, bool* visited, int* stack, int* stackIndex, int V) {
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all adjacent vertices
    for (int i = 0; i < V; i++) {
        if (adj[v][i] && !visited[i]) {
            topologicalSortUtil(i, adj, visited, stack, stackIndex, V);
        }
    }

    // Push current vertex to stack which stores the result
    stack[(*stackIndex)++] = v;
}

// Function to perform Topological Sort
void topologicalSort(int** adj, int V) {
    int* stack = malloc(V * sizeof(int));
    bool* visited = malloc(V * sizeof(bool));
    int stackIndex = 0;

    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    // Call the recursive helper function to store
    // Topological Sort starting from all vertices one by one
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, adj, visited, stack, &stackIndex, V);
        }
    }

    // Print contents of stack
    for (int i = stackIndex - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");

    free(stack);
    free(visited);
}

int main() {
    int V, E;

    // Input number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    // Initialize adjacency matrix
    int** adj = malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        adj[i] = calloc(V, sizeof(int));
    }

    // Input edges
    printf("Enter the edges (u v) where there is an edge from u to v:\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < V && v >= 0 && v < V) {
            adj[u][v] = 1;
        } else {
            printf("Invalid edge (%d %d), skipping.\n", u, v);
        }
    }

    printf("Topological sorting of the graph: ");
    topologicalSort(adj, V);

    // Free adjacency matrix memory
    for (int i = 0; i < V; i++) {
        free(adj[i]);
    }
    free(adj);

    return 0;
}

