//recursive sum of digits of a number

#include <stdio.h>
int sum_of_digits(int n) 
{
    if (n == 0) {
        return 0;
    }
    return (n % 10) + sum_of_digits(n / 10);
}

// //reverse of a number using recursion
// int reverse_number(int n, int rev)
// {
//     if (n == 0) {
//         return rev;
//     }
//     rev = rev * 10 + (n % 10);
//     return reverse_number(n / 10, rev);
// }

int main()
{
    int n;
    scanf("%d",&n);
    printf("Sum of digits: %d\n", sum_of_digits(n));
    return 0;
}

