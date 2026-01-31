//program for printing max of number using macros
#include<iostream>
#include<iomanip>

#define MAX(a,b) ((a>b)?(a):(b))

using namespace std;

int main(int argc,char* argv[])
{
   cout<<"max number:"<<MAX(3,5)<<endl;
   cout<<"max number:"<<MAX(7,20)<<endl;
   return 0;
}