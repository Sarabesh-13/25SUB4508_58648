// nested ternary operator example

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a = 10, b = 20, c = 30;
    int max;
    max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
    printf("The maximum value is: %d\n", max);
    return 0;
}