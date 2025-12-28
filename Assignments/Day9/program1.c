// find largest of three numbers

#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    int a,b,c;
    printf("Enter three numbers: ");
    scanf("%d %d %d",&a,&b,&c);
    printf("Largest number is: %d\n", (a>b)?((a>c)?a:c):((b>c)?b:c));
    return 0;
}
