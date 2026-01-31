//program for abc pattern

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        for(int space=0;space<n-i;space++)
        {
            printf(" ");
        }
        char a='A';
        for(int j=i;j<2*i;j++)
        {
            printf("%c",a);
            a+=1;
        }
        char b=a-2;
        for(int k=2;k<=i;k++)
        {
            printf("%c",b);
            b-=1;
        }
        printf("\n");

    }
}