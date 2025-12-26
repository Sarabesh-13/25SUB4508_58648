// program cyclic swap of three numbers using call by reference

#include <stdio.h>
#include <stdlib.h>

void cyclicSwap(int *a, int *b, int *c)
{
    int temp;
    temp = *b;
    *b = *c;
    *c = *a;
    *a = temp;
}


int main()
{
 int a=1, b=2, c=3;
    printf("Before swapping: a=%d, b=%d, c=%d\n", a, b, c);
    cyclicSwap(&a, &b, &c);
    printf("After swapping: a=%d, b=%d, c=%d\n", a, b, c);
    return 0;
}