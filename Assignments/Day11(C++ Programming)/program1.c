//program for finding subarray sum

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main()
{
int n;
printf("\nEnter the number\n");
scanf("%d",&n);
int arr[n];
bool flag=true;
for(int i=0;i<n;i++)
{
    printf("Enter the array element %d: ",i+1);
    scanf("%d",&arr[i]);
}
for(int i=0;i<n;i++)
{
  int start=i;
  int sum=0;
  for(int j=i;j<n;j++)
  {
    sum+=arr[j];
    if(sum==n)
    {
        flag=false;
        int end=j;
        printf("Sum found between index %d and %d",start,end);
        break;
    }
    else if(sum>n)
    {
        break;
    }
  }   
}
if(flag)
{
 printf("No subarray found");
}
}