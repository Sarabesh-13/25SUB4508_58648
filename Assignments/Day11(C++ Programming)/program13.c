//program to reverse a number 
#include<stdio.h>
#include<stdlib.h>


int reverse(int n,int rev)
{
    if(n==0)
    {
        return rev;
    }
    rev=rev*10+n%10;
    reverse(n/10,rev);
}

int main()
{
    int n;
    printf("enter a number: ");
    scanf("%d",&n);
    int r=0;
    printf("%d",reverse(n,r));
    return 0;
}