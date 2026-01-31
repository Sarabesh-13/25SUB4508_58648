//program to find god numbers,(i.e) numbers which are only divisible by 2,3,5
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 200

bool is_godNumber(int n)
{
     if(n==2||n==3)
     {
        return true;
     }
     bool f1=true,f2=true,f3=true;
     int temp1=n,temp2=n,temp3=n;
     while(temp1%2==0)
     {
        temp1=temp1/2;
     }
     while(temp2%3==0)
     {
        temp2=temp2/3;
     }
     while(temp3%5==0)
     {
        temp3=temp3/5;
     }
     return (temp1==1&&temp2==1&&temp3==1);
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