//program for determine valid triangle and find perimeter and area

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    float a,b,c,s,area,perimeter;
    printf("Enter the three sides of triangle:\n");
    scanf("%f%f%f",&a,&b,&c);
    if((a+b>c)&&(b+c>a)&&(c+a>b))
    {
        printf("Valid triangle\n");
        perimeter=a+b+c;
        s=perimeter/2;
        area=sqrt(s*(s-a)*(s-b)*(s-c));
        printf("Perimeter of triangle: %.2f\n",perimeter);
        printf("Area of triangle: %.2f\n",area);
    }
    else
    {
        printf("Not a valid triangle\n");
    }
    return 0;
}
