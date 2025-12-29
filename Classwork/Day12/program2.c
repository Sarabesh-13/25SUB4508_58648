//program for alternative merge for two strings

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX 999

int main()
{
    char str1[999];
    printf("enter the string 1: ");
    fgets(str1,sizeof(str1),stdin);
    str1[strcspn(str1,"\n")]='\0';
    char str2[999];
    printf("enter the string 2: ");
    fgets(str2,sizeof(str2),stdin);
    str2[strcspn(str2,"\n")]='\0';
    bool flag=true;
    int min_length=(strlen(str1)>strlen(str2))?(strlen(str2)):(strlen(str1));
    int i=0;
    if(strlen(str1)<strlen(str2))
    {
        flag=false;
        printf("first string length is minimum %d\n",strlen(str1));
    }
    else
    {
      printf("second string length is minimum %d\n",strlen(str2));
    }
    while(i<min_length)
    {
        printf("%c%c",str1[i],str2[i]);
        i+=1;
    }
    if(!flag)
    {
        int remaining_length=i;
        while(remaining_length<strlen(str2))
        {
            printf("%c",str2[remaining_length]);
            remaining_length+=1;
        }
    }
    else
    {
       int remaining_length=i;
      while(remaining_length<strlen(str1))
        {
            printf("%c",str1[remaining_length]);
            remaining_length+=1;
        }
    }
    return 0;
}