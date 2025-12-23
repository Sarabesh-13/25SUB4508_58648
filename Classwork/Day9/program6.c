// program to check eligibility to vote using conditional operator
#include<stdio.h>

int main()
{
    int age;
    scanf("%d",&age);
    printf("%s",(age>=18)?"elligible":"not elligible");
    if(age>=18)
    {
        printf("eligible");
    }
    else
    {
    printf("not eligible");
    }
}