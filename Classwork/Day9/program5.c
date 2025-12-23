// program to print ascii value of each character in a string and read string with spaces
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char str[101];
    scanf("%[^\n]",str);
    for(int i=0;i<strlen(str);i++)
    {
        printf("char for = %c,ascii = %d",str[i],str[i]);
    }
    printf("%s",str);
}