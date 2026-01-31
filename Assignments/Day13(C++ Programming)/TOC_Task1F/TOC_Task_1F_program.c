// observe layout of data in memory using gdb

#include <stdio.h>
#include <stdlib.h>

void change1(int a)
{
    int c=a+10;
    printf("%d\n",c);
}

void change(int a)
{
    int c=a+5;
    printf("%d\n",c);
    change1(a);
}



int main() 
{
int a=20;
change(20);
return 0;
}