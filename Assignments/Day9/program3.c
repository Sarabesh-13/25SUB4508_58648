//program to calculate compound interest

#include <stdio.h>
#include <math.h>

int main() {
    double principal, rate, time, compound_interest, amount;

    // Input principal amount, rate of interest and time period
    printf("Enter principal amount: ");
    scanf("%lf", &principal);
    printf("Enter annual rate of interest (in percentage): ");
    scanf("%lf", &rate);
    printf("Enter time period (in years): ");
    scanf("%lf", &time);

    // Calculate compound interest
    amount = principal * pow((1 + rate / 100), time);
    compound_interest = amount - principal;

    // result
    printf("Compound Interest after %.2lf years: %.2lf\n", time, compound_interest);
    printf("Total Amount after %.2lf years: %.2lf\n", time, amount);

    return 0;
}