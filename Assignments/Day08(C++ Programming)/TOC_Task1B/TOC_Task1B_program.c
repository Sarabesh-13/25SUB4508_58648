// bit operations in c

#include <stdio.h>
#include<stdlib.h>

int main() {
    unsigned int a;
    printf("Enter a positive integer: ");
    scanf("%u", &a);

    //count the number of set bits in integer a
    int count = 0;
    unsigned int temp = a;
    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    printf("Number of set bits in %u is: %d\n", a, count);

    //get the value of ith bit
    int i;
    printf("Enter the bit position to get (0-indexed): ");
    scanf("%d", &i);
    unsigned int ith_bit = (a >> i) & 1;
    printf("The value of the %dth bit is: %u\n", i, ith_bit);

    //set the ith bit
    printf("Setting the %dth bit.\n", i);
    a |= (1 << i);
    printf("New value after setting the %dth bit: %u\n", i, a);

    //toggle the ith bit
    printf("Toggling the %dth bit.\n", i);
    a ^= (1 << i);
    printf("New value after toggling the %dth bit: %u\n", i, a);
    return 0;
}