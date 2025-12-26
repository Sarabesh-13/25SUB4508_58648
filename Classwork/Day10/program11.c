//calculate sum of series of number with power 4^n

#include <stdio.h>
#include <math.h>

int main() {
    int n, i;
    double sum = 0.0;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        sum += pow(4, i);
    }

    printf("The sum of the series is: %.2f\n", sum);

    return 0;
}