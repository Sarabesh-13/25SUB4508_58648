//program for finding leader of the array

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main()
{
    int n;
    printf("enter the number: ");
    scanf("%d",&n);
    int max=INT_MIN;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        printf("enter the arary values arr[%d]=",i+1);
        scanf("%d",&arr[i]);
    }
    for(int j=n-1;j>=0;j--)
    {
        if(arr[j]>max)
        {
            max=arr[j];
            printf("%d ",max);
        }
    }

}