//find two numbers are equal without using comparison operator

#include <stdio.h>

int are_equal(int a, int b) 
{
    return !(a ^ b);
}

int main() 
{
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    if (are_equal(num1, num2)) {
        printf("The numbers are equal.\n");
    } else {
        printf("The numbers are not equal.\n");
    }
    
    return 0;
}