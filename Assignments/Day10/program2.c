//find nth term of fibonacci series

#include<stdio.h>
#include<stdlib.h>
#include "math.h"

int main()
{
    int n;
    printf("Enter the value of n: ");
    scanf("%d",&n);
    float phi = (1 + sqrt(5)) / 2;
    float psi = (1 - sqrt(5)) / 2;
    float fib_n = (pow(phi, n) - pow(psi, n)) / sqrt(5);
    int fibonacci_n = round(fib_n);
    printf("The %dth term of the Fibonacci series is: %d\n", n, fibonacci_n);
    return 0;
}