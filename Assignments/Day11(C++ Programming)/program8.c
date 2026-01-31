//program for storing array from 1 to 100

#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 100


int main()
{
int arr[MAX_SIZE];
for(int i=0;i<=100;i++)
{
    arr[i]=i+1;
} 
for(int i=0;i<100;i++)
{
    printf("%d ",arr[i]);
}
return 0;
}