// program for bitwise AND, OR and NOT operations and ~ operator

#include <stdio.h>
#include<stdlib.h>

int main()
{
    int a = 29; 
    int b = 15;

    
    int and_result = a & b; 
    printf("Bitwise AND of %d and %d is: %d\n", a, b, and_result);

    
    int or_result = a | b; 
    printf("Bitwise OR of %d and %d is: %d\n", a, b, or_result);

    
    int not_result = ~a; 
    printf("Bitwise NOT of %d is: %d\n", a, not_result);

    int xor_result = a ^ b; 
    printf("Bitwise XOR of %d and %d is: %d\n", a, b, xor_result);
    return 0;
}