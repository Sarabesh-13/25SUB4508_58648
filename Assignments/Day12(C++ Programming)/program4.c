//program to remove a word in string
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 999
#define MIN 20


int main()
{
    char str1[MAX],str2[MAX];
    printf("Enter the string: ");
    scanf("%[^\n]",str1);
    printf("Enter the word to remove: ");
    scanf("%s",str2);
    for(int i=0;i<strlen(str1);i++)
    {
        char str3[MIN];
        int t=0;
        while(isalnum(str1[i]))
        {
            str3[t++]=str1[i++];
        }
        str3[t]='\0';
        if(strcmp(str2,str3)==0)
        {
            printf(" ");
        }
        else{
            printf("%s ",str3);
        }
    }
    return 0;
}