/* Program to demonstrate the use of increment operators */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a,b,c;
    a=10;
    b=a++; //b=10,a=11
    c=++b; //b=11 c=11
    a++; //a=11
    ++b; //b=12
    printf(" %d %d %d",++a,b++,c++); a=13,b=12,c=11 
}