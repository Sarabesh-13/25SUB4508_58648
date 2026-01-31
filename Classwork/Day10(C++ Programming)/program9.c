//reverse array by swapping first half with second half

#include <stdio.h>
#include<stdlib.h>

int main()
{
 int arr[]={1,2,3,4,5,6,7,8,9};
 int n=sizeof(arr)/sizeof(arr[0]);
 int i,j;
 for(i=0,j=n/2;i<n/2;i++,j++)
 {
     int temp=arr[i];
     arr[i]=arr[j];
     arr[j]=temp;
 }
    for(i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
}