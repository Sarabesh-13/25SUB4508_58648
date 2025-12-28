//remove duplicates from an array

#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100

int main()
{
    int n,i,k=0;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[MAX_SIZE]; 

    printf("Enter %d elements:\n", n);
    for (i=0;i<n;i++) {
       scanf("%d", &arr[i]);
    }

    int arr1[MAX_SIZE];

    for (i=0;i<n;i++)
    {
       int flag=1;
       for(int j=0;j<k;j++)
       {
          if(arr[i]==arr[j])
          {
              flag=0;
          }
       }
       if(flag)
       {
        printf("%d",flag);
        arr1[k++]=arr[i];
       }
    }

    printf("Array after removing duplicates:\n");
    for (i=0;i<k;i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    return 0;
}