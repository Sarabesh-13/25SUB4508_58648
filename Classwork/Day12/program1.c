#include<stdio.h>
#include<stdlib.h>

void get_input(int* arr,int n)
{
    printf("Enter the array elements: \n");
   for(int i=0;i<n;i++)
   {
      scanf("%d",arr+i);
   }
}
void sort_descending(int* arr,int n)
{
    for(int i=0;i<n-1;i++)
   {
    for(int j=i+1;j<n;j++)
    {
        if((*(arr+i))<(*(arr+j)))
        {
            int t=(*(arr+i));
            (*(arr+i))=(*(arr+j));
            (*(arr+j))=t;
        }
    }
}
}

void sort_ascending(int* arr,int n)
{
    for(int i=0;i<n-1;i++)
   {
    for(int j=i+1;j<n;j++)
    {
        if((*(arr+i))>(*(arr+j)))
        {
            int t=(*(arr+i));
            (*(arr+i))=(*(arr+j));
            (*(arr+j))=t;
        }
    }
}
}

void display(int* arr,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",*(arr+i));
    }
    print("\n");
}

int main()
{
   int n;
   printf("enter the integer: ");
   scanf("%d",&n);
   int *arr=(int*)malloc(n*sizeof(int));
   get_input(arr,n);
   display(arr,n);
   sort_ascending(arr,n);
   display(arr,n);
   sort_descending(arr,n);
   display(arr,n);
   return 0; 
}