//program to find sum of two distinct numbers are equal
#include <stdio.h>
#include<stdlib.h>


int main()
{
    int n1;
    printf("enter first number: ");
    scanf("%d",&n1);
    int n2;
    printf("enter second number: ");
    scanf("%d",&n2);
    int sum1=0,sum2=0;
    int arr[10];
    for(int i=0;i<10;i++)
    {
        arr[i]=0;
    }
    while(n1!=0)
    {
        int r=n1%10;
        if(arr[r]!=r)
        {
          arr[r]=r;
          sum1+=r;
        }
        n1/=10;
    }
    while(n2!=0)
    {
        int r=n2%10;
        if(arr[r]!=(r+1))
        {
            arr[r]=r+1;
            sum2+=r;
        }
        n2/=10;
    }
    printf("%s",((sum1==sum2)?("YES"):("NO")));
    return 0;
}