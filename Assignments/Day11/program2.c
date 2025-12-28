//program for finding equilibrium state

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    int arr[n];
    bool flag=false;
    for(int i=0;i<n;i++)
    {
        printf("enter a number for array element %d: ",i+1);
        scanf("%d",&arr[i]);
    }
    for(int i=0;i<n;i++)
    {
        int prefix_sum=0;
        int suffix_sum=0;
        int index=i;
        for(int j=0;j<i;j++)
        {
            prefix_sum+=arr[i];
        }
        for(int k=i+1;k<n;k++)
        {
            suffix_sum+=arr[i];
        }
        if(prefix_sum==suffix_sum && prefix_sum!=0)
        { 
            flag=true;
            printf("%d",index);
            break;
        }
    }
    if(!flag)
    {
        printf("-1");
    }
    return 0;
}