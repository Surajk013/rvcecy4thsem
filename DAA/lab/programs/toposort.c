#include <stdio.h>
#include <stdlib.h>
int topo[10], k;

void dfs(int a[][10], int n, int v[], int source) {
    int i;

    v[source] = 1;//making one node [current/source] as visited

    for (i = 1; i <= n; i++) {
        if (!v[i] && (a[source][i])) {//if there exists a unvisited node (!v[i]) and a edge form the current [source] to the unvisited node then :
            dfs(a, n, v, i);// run dfs towards that node
        }
    }

    topo[++k] = source;// lastly add the source[current] node to the topo order -- yes the one found first is added in the last [reverse of actual topo]
}

int main() {
    int n, a[10][10], i, v[10] = {}, j;// v[10] = {} as this type of initialisation declares all the elements as '0' ensuring there is no edge

    printf("\nEnter the number of nodes : ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);

    // the printing of the graph is optional
    printf("\nThe grpah is as follows :\n");

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            printf("%d ", a[i][j]);

        printf("\n");
    }

    for (i = 1; i <= n; i++) {
        if (v[i] == 0) // running dfs on all unvisited nodes
            dfs(a, n, v, i);
    }

    printf("\nTopological Ordering is : ");

    for (i = k; i >= 1; i--)
        printf("%d ", topo[i]);

    printf("\n");

    return 0;
}