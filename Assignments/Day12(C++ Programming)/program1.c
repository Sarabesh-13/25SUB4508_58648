//program for expressing given number as sum of two prime number
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

bool is_prime(int n)
{
    if(n<2)
    {
        return false;
    }
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    printf("enter the positive integer: ");
    scanf("%d",&n);
    int ways=0;
    if(n<=1)
    {
        printf("NoofWays: %d",ways);
        return 1;
    }
    for(int i=2;i<n;i++)
    {
        if(is_prime(i))
        {
            int complement=n-i;
            if(is_prime(complement))
            {
                printf("%d = %d + %d\n",n,i,complement);
                ways++;
            }
        }
    }
    printf("NoofWays = %d",ways);
    return 0;
}