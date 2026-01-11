//program for printing 2d matrix using pointers with O(n^2) complexity
#include<iostream>
#include<iomanip>

#define ROW 3
#define COL 3

using namespace std;

int main(int argc,char* argv[])
{
   int arr[ROW][COL]={1,2,3,4,5,6,7,8,9};
   for(int(*ptr)[ROW]=arr;ptr!=arr+ROW;ptr++)
   {
    for(int *ptr1=*ptr;ptr1!=*ptr+COL;ptr1++)
    {
        cout<<*ptr1<<" ";
    }
   }
   return 0;
}