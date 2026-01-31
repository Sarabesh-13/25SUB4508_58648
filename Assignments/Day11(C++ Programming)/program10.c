//program for finding sum of even and odd values in array

#include<stdio.h>
#include<stdlib.h>

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
    int odd_sum=0,even_sum=0;
    for(int i=0;i<n;i++)
    {
       if(arr[i]%2==1)
       {
        odd_sum+=arr[i];
       }
       else{
        even_sum+=arr[i];
       }
    }
    printf("Odd Sum = %d\n",odd_sum);
    printf("Even Sum = %d\n",even_sum);
}



