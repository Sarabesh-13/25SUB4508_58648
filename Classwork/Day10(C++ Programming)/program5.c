//break the amount into smallest bank notes
#include <stdio.h>
#include<stdlib.h>

int main()
{
    int amount, original_amount;
    int notes_100, notes_50, notes_20, notes_10, notes_5, notes_2, notes_1;

    printf("Enter the amount: ");
    scanf("%d", &amount);
    original_amount = amount;

    notes_100 = amount / 100;
    amount %= 100;

    notes_50 = amount / 50;
    amount %= 50;

    notes_20 = amount / 20;
    amount %= 20;

    notes_10 = amount / 10;
    amount %= 10;

    notes_5 = amount / 5;
    amount %= 5;

    notes_2 = amount / 2;
    amount %= 2;

    notes_1 = amount / 1;
    amount %= 1;

    printf("Breakdown of %d into smallest bank notes:\n", original_amount);
    if (notes_100 > 0) printf("100: %d\n", notes_100*100);
    if (notes_50 > 0) printf("50: %d\n", notes_50*50);
    if (notes_20 > 0) printf("20: %d\n", notes_20*20);
    if (notes_10 > 0) printf("10: %d\n", notes_10*10);
    if (notes_5 > 0) printf("5: %d\n", notes_5*5);
    if (notes_2 > 0) printf("2: %d\n", notes_2*2);
    if (notes_1 > 0) printf("1: %d\n", notes_1);

    return 0;
}