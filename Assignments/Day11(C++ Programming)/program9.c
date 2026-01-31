//program for reversing array

#include<stdio.h>
#include<stdlib.h>

void reverse(int *arr,int start,int low)
{
    while(start<=low)
    {
        int temp = arr[start];
        arr[start]=arr[low];
        arr[low]=temp;
        start++;
        low--;
    }
}


int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
    {
        printf("enter array element arr[%d]: ",i+1);
        scanf("%d",&arr[i]);
    }
    reverse(arr,0,n-1);
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
}