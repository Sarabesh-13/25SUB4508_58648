//program for printing 2d matrix using pointers with O(n) complexity
#include<iostream>
#include<iomanip>

#define ROW 3
#define COL 3

using namespace std;

int main(int argc,char* argv[])
{
   int arr[ROW][COL]={1,2,3,4,5,6,7,8,9};
   int (*ptr)=&arr[0][0];
   int size=ROW*COL;
   for(int i=0;i<size;i++)
   {
    cout<<*(ptr+i)<<" ";
    if((i+1)%COL==0)
    {
        cout<<'\n';
    }
   }
   return 0;
}