// program for bitwise AND, OR and NOT operations and ~ operator

#include <stdio.h>
#include<stdlib.h>

int main()
{
    int a = 29; // Binary: 0001 1101
    int b = 15; // Binary: 0000 1111

    // Bitwise AND
    int and_result = a & b; // Result: 0000 1101 (13 in decimal)
    printf("Bitwise AND of %d and %d is: %d\n", a, b, and_result);

    // Bitwise OR
    int or_result = a | b; // Result: 0001 1111 (31 in decimal)
    printf("Bitwise OR of %d and %d is: %d\n", a, b, or_result);

    // Bitwise NOT
    int not_result = ~a; // Result: 1110 0010 (-30 in decimal, two's complement)
    printf("Bitwise NOT of %d is: %d\n", a, not_result);

    int xor_result = a ^ b; // Result: 0001 0010 (18 in decimal)
    printf("Bitwise XOR of %d and %d is: %d\n", a, b, xor_result);
    return 0;
}