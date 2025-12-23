// program to estimate the time to complete based on weight of clothes
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int option;
    printf("Enter a option\n");
    printf("\n 1 0-1kg");
    printf("\n 2 1-2kg");
    printf("\n 3 2-3kg");
    printf("\n 4 3-5kg");
    printf("\n your choice");
    scanf("%d", &option);
    if (option == 1)
    {
        printf("\nEstimated time to complete 15 mins");
    }
    else if (option == 2)
    {
        printf("\nEstimated time to complete 30 mins");
    }
    else if (option == 3)
    {
        printf("\nEstimated time to complete 45 mins");
    }
    else if (option == 4)
    {
        printf("\nEstimated time to complete 60 mins");
    }
    else
    {
        printf("\n Choose a correct option to make option work\n");
    }
    printf("\n Machine work completed");
}