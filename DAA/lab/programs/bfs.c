#include<stdio.h>
#include<conio.h>

int a[20][20],q[20],visited[20], n,i,j, f =0, r=-1;

void bfs(int v){
    visited[v] =1;
    q[++r]= v;

    while(f<=r){
        v = q[f++];
        for (i = 1; i <= n; i++) {
            if (a[v][i] && !visited[i]) {
                q[++r] = i;
                visited[i] = 1;
            }
        }

    }
}

int main(){
    int v=1, count =0;
    printf("\nEnter no. of vertices: ");
    scanf("%d", &n);

    for(i=1;i<=n;i++){
        q[i] = 0;
        visited[i] =0;
    }

    printf("\nEnter graph data:\n");
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            scanf("%d", &a[i][j]);

    bfs(v);

    for(i=1;i<=n;i++)
        if(visited[i])
            count++;

    if(count==n)
        printf("\nConnected");
    else
        printf("\nNot connected");

    return 0;

}