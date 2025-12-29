//program for reversing word of a given string
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 999
#define MIN 20

void reverse(char *string,int start,int low)
{
    while(start<=low)
    {
        int temp = string[start];
        string[start]=string[low];
        string[low]=temp;
        start++;
        low--;
    }
}


int main()
{
    char str[999];
    printf("Enter the string: ");
    scanf("%[^\n]",str);
    int n=strlen(str);
    for(int i=0;i<n;i++)
    {
       int t=0;
       char word[MIN];
       while(isalnum(str[i]))
       {
        word[t++]=str[i++];
       }
       word[t]='\0';
       reverse(word,0,t-1);
       printf("%s\t",word);
    }
}