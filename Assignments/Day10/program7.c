//program for gcd of three numbers

#include <stdio.h>
#include<stdlib.h>

int gcd(int a, int b) 
{
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


int main() 
{
    int num1, num2, num3, result;

    printf("Enter three integers: ");
    if (scanf("%d %d %d", &num1, &num2, &num3) != 3) {
        printf("Invalid input. Please enter three integers.\n");
        return 1;
    }

    result = gcd(gcd(num1, num2), num3);

    printf("GCD of %d, %d and %d is %d\n", num1, num2, num3, result);

    return 0;
}