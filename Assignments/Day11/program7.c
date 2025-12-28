//program to find gcd of given list in such way that removing exactly one element and then taking GCD will be max

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

int gcd(int a,int b)
{
    // printf("%d %d\n",a,b);
    while(b!=0)
    {
        int temp=b;
        b=a%b; //calculate the remainder
        a=temp; //assign old num2 to num1
    }
    return a;
}

int main()
{
  int n;
  printf("Enter a number: ");
  scanf("%d",&n);
  int arr[n];
  for(int i=0;i<n;i++)
  {
    printf("enter a number %d:",i+1);
    scanf("%d",&arr[i]);
  }
  int res=INT_MIN;
  int i;
  for(i=0;i<n-1;i++)
  {
    res=MAX(res,gcd(arr[i],arr[i+1]));
  }
  printf("%d",res);
  return 0;
}