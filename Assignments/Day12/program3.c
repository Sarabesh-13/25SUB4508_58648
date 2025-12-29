//program to replace lowercase to uppercase and vice versa

#include<stdio.h>
#include<stdlib.h>

#define MAX 999

int main()
{
    char str[999];
    printf("enter the string: ");
    scanf("%[^\n]",str);
    int i=0;
    while(str[i]!='\0')
    {
        if(str[i]>=97 && str[i]<=122)
        {
            str[i]-=32;
        }
        else if(str[i]>=65 && str[i]<=90)
        {
            str[i]+=32;
        }
        printf("%c",str[i]);
        i+=1;
    }
    return 0;
}