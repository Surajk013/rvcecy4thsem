#include<stdio.h>
#include<stdlib.h>
#define INF 999

void prims(int n, int cost[10][10]){
    int i,j,min,u,v,visited[10], mincost = 0,e=1;
    for(i=1;i<=n;i++)
        visited[i] = 0;

    visited[1] = 1;
    while(e<n){
        min = INF;
        for(i=1;i<=n;i++){
            if(visited[i]){
                for(j=1;j<=n;j++){
                    if(!visited[j] && cost[i][j]<min){
                        min = cost[i][j];
                        u=i;
                        v=j;
                    }
                }
            }
        }
        if(!visited[v]){
            printf("\nEdge %d = (%d %d) cost: %d", e++, u, v ,min);
            mincost+=min;
            visited[v] =1;
        }
        cost[u][v] = cost[v][u] = INF;
    }
    printf("\nTotal Cost = %d", mincost );
}

int main(){
    int n,i,j , cost[10][10];
    printf("\nEnter the no. of nodes: ");
    scanf("%d", &n);

    printf("\nEnter the adjacency matrix: \n");
    for(i=1;i<=n;i++){
        printf("\nEnter the elements in row %d: " ,i);
        for(j=1;j<=n;j++){
            scanf("%d", &cost[i][j]);
            if(cost[i][j] == 0){
                cost[i][j] = INF;
            }
        }
    }
    prims(n,cost);
    return 0;
}