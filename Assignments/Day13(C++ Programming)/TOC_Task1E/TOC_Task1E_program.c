// observe layout of data in memory using gdb

#include <stdio.h>
#include <stdlib.h>



int main() 
{
int x=20;
int *a=&x;
int **b=&a;
**b=(**b)*10;
printf("changed value of x=%d\n",x);
printf("changed value of x in pointer a=%d\n",*a);
printf("changed value of x in pointer b=%d\n",**b);
printf("Address of x %p\n",&a);
printf("Address of x in pointer a %p\n",a);
printf("Address of x in double pointer b %p\n",*b); 
return 0;
}