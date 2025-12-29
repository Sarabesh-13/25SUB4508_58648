//program to find the Nth prime number
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
    int N;
    printf("Enter the Nth number: ");
    scanf("%d",&N);
    int count=0,i=1;
    while(count<N)
    {
        if(is_prime(i))
        {
            printf("%d ",i);
            count++;
            i++;
        }
        else
        {
            i++;
        }
    }
    return 0;
}