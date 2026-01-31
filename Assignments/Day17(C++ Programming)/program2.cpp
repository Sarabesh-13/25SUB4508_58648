//program to print floating point number with precision
#include<iostream>
#include<iomanip>


int main(int argc,char* argv[])
{
   float pi=3.1428f;
   int a=2;
   std::cout<<std::fixed<<std::setprecision(a)<<pi;
   return 0;
}