//print nth row of pascal triangle

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n;
    printf("Enter the row number: ");
    scanf("%d", &n);
    int prev=1;
    for(int i=0;i<=n;i++)
    {
        printf("%d ",prev);
        prev=prev*(n-i)/(i+1);
    }
}