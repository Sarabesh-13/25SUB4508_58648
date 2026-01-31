//write a program to find frequency of each character in string
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

#define MAX 256

typedef struct 
{
    char ch;
    int frequency;

}HashMap;

void init (HashMap *array)
{
    for(int i=0;i<MAX;i++)
    {
      if((i>=48 && i<=57) || (i>=97 && i<=122) || (i>=65 && i<=90))
      {
        array[i].ch=i;
        array[i].frequency=0;
      }
    }
}


int main()
{
    HashMap array[MAX];
    init(array);
    char str[999];
    int index=0;
    printf("enter the string: ");
    scanf("%[^\n]",str);
    for(int i=0;str[i]!='\0';i++)
    {
        if((str[i]>=48 && str[i]<=57) || (str[i]>=97 && str[i]<=122) || (str[i]>=65 && str[i]<=90))
        {
            array[str[i]].frequency+=1;
        }
    }
    for(int i=0;i<MAX;i++)
    {
        if(((i>=48 && i<=57) || (i>=97 && i<=122) || (i>=65 && i<=90)) && array[i].frequency>0)
        {
            printf("\n%c = %d\n",array[i].ch,array[i].frequency);
        }
    }
}