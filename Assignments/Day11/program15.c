//program to find god numbers,(i.e) numbers which are only divisible by 2,3,5
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 200

bool is_godNumber(int n)
{
     if(n==1||n==2||n==3)
     {
        return true;
     }
     return (n%2==0||n%3==0||n%5==0);
}



int main()
{
    int n;
    printf("Enter the number: ");
    scanf("%d",&n);
    int count=0,i=1;
    while(count<n)
    {
        if(is_godNumber(i))
        {
            printf("%d ",i);
            count+=1;
        }
        i++;
    }
    return 0;   
}