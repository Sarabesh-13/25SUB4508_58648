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


bool is_prime_digits(int n)
{
    int c2=0;
    int c1=0;
    while(n>0)
    {
        int r=n%10;
        if(is_prime(r))
        {
           c2+=1;
        }
        c1+=1;
        n/=10;
    }
    return (c1==c2);
}

int main()
{
    int N;
    printf("Enter the Nth number: ");
    scanf("%d",&N);
    int count=0,i=1;
    while(count<N)
    {
        if(is_prime_digits(i))
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