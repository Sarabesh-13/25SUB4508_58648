//program to find perfect square
#include <stdio.h>
#include <math.h>
#include<stdlib.h>

int main()
{
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    float n = (float)100;
    float x = sqrt(num);
    float y = 0.1;
    while((x-y)>0.00001)
    {
        x = (x + y) / 2;
        y = n / x;
    }
    if(x == y)
        printf("The number is a perfect square.\n");
    else
        printf("The number is not a perfect square.\n");
    return 0;
}