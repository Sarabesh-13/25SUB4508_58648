//program for finding sum of odd position and even position values

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
    int odd_position_sum=0,even_position_sum=0;
    for(int i=0;i<n;i++)
    {
       if(i%2==1)
       {
        odd_position_sum+=arr[i];
       }
       else{
        even_position_sum+=arr[i];
       }
    }
    printf("Odd Position Sum = %d\n",odd_position_sum);
    printf("Even Position Sum = %d\n",even_position_sum);
    return 0;
}