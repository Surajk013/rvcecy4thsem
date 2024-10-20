#include<stdio.h>
#include<stdlib.h>
#define size 100
int topo[10],k;

void dfs(int a[][10],int n,int v[],int source){
	int i;
	v[source]=1;
	for(i=1;i<=n;i++){
		if(!v[i] && (a[source][i]))
			dfs(a,n,v,i);
	}
	topo[++k]=source;
}

int main(){
	int a[10][10],v[10]={},i,j,n;
	printf("\n Enter the number of nodes: ");
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		printf("\nFrom edge %d, ",i);
		for(j=1;j<=n;j++){
			printf("\n is there an edge to %d: ",j);
			scanf("%d",&a[i][j]);
		}
	}
	for(i=1;i<=n;i++){
		if(v[i]==0)
			dfs(a,n,v,i);
	}

	printf("\nThe topological order is: ");
	for(i=k;i>=1;i--)
		printf("%d ",topo[i]);

	printf("\n");
	return 0;
}
