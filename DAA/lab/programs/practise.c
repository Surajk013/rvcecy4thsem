#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 10

void shifttable(char p){

}

int horspool(char t,char p){
    int n,m,i,j;
    n=strlen(t);
    m=strlen(p);
    shifttable(p)
    i=m-1;
    while(i<=n-1){

    }
}

int main()
{
    char t[250], p[10];
    printf("\nEnter the Text :");
    scanf("%s", t);
    printf("%d",strlen(t));
    printf("\nEnter the Pattern :");
    scanf("%s", p);
    int flag = Horspool(t, p);
    if (flag == -1)
        printf("\nPattern not present in the text\n");
    else
        printf("Pattern is found at index %d\n", flag);
    return 0;
}