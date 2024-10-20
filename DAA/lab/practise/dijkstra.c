#include<stdio.h>
#include<stdlib.h>
#define inf 999
int n,v[10],d[10],cost[10][10];
void dijkstra(int cost[10][10],int n,int sourcenode,int v[10],int d[10]){
    int min,j,i,u;
    v[sourcenode]=1;
    for(i=1;i<=n;i++){
        min=inf;
        for(j=1;j<=n;j++){
            if(v[j]==0 && d[j]<min){
                min=d[j];
                u=j;
            }
        }
        v[u]=1;
        for(j=1;j<=n;j++){
            if(v[j]==0 && (d[j]>(d[u]+cost[u][j])))
                d[j]=d[u]+cost[u][j];
        }
    }
}

int main(){
    int i,j;
    printf("\n Enter the number of nodes: ");
    scanf("%d",&n);
    printf("\n Enter the cost matrix: ");
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
        scanf("%d",&cost[i][j]);
        }
    }
    int sourcenode;
    // printf("Enter the source node between %d and %d ",1,n);
    // scanf("%d",&sourcenode);
    for(sourcenode=1;sourcenode<=n;sourcenode++){
        for(i=1;i<=n;i++){
            d[i]=cost[sourcenode][i];
            v[i]=0;
        }
        dijkstra(cost,n,sourcenode,v,d);
        printf("\n The shortest path form source node is: ");
        for(i=1;i<=n;i++){
            printf("%d-->%d=%d\n\n",sourcenode,i,d[i]);
        }
    }
    return 0;
}