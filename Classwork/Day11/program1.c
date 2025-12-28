#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    int second=0;
    if(n>=1)
    printf("%d ",second);
    for(int i=2;i<=n;i++)
    {
        second=second+(2*i-1);
        printf(",%d ",second);
    }
}