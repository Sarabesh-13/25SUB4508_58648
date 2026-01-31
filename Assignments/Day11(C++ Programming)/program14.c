/* 
program for comma seperated list integer as input.for each integer n in first list,
the programs needs to find the count of its occurence C in the second list.
the program should print the N-C for each integer.
*/

#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 999

typedef struct
{
    int number;
    int frequency;
    
}HashMap;

void init(HashMap arr[])
{
 for(int i=0;i<MAX_SIZE;i++)
 {
    arr[i].number=0;
    arr[i].frequency=0;
 }
}


int main()
{
    int n1;
    int arr1[MAX_SIZE];
    printf("Enter a size of first array: ");
    scanf("%d",&n1);
    for(int i=0;i<n1;i++)
    {
        printf("Enter array element values arr1[%d]: ",i);
        scanf("%d",&arr1[i]);
    }
    HashMap array[MAX_SIZE];
    init(array);
    for(int i=0;i<n1;i++)
    {
        array[arr1[i]].number=arr1[i];
    }
    int n2;
    int arr2[MAX_SIZE];
    printf("Enter a size of second array: ");
    scanf("%d",&n2);
    for(int i=0;i<n2;i++)
    {
        printf("Enter array element values arr2[%d]: ",i);
        scanf("%d",&arr2[i]);
    }
    for(int i=0;i<n2;i++)
    {
        if(array[arr2[i]].number==arr2[i])
        {
            array[arr2[i]].frequency+=1;
        }
    }
    for(int i=0;i<MAX_SIZE;i++)
    {
        if(array[i].frequency!=0)
        {
            printf("%d-%d\n",array[i].number,array[i].frequency);
        }
    }
    return 0;
}