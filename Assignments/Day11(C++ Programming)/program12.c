//program to print 1 to 100 without loop,rec,goto
#include <stdio.h>

void fun(int n)
{
    if(n>1)
    {
        n-=1;
        if(n>1)
        {
           fun(n); 
        }
    }
    printf("%d ",n);
}

int main()
{
   fun(101);
}