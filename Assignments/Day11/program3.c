//write a program to find frequency of each character in string
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

#define MAX 256

typedef struct 
{
    char string[20];
    int ascii_sum;
    int frequency;

}HashMap;

void init (HashMap *array)
{
    for(int i=0;i<MAX;i++)
    {
      array[i].ascii_sum=0;
      array[i].frequency=0;
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
        bool flag=false;
        int asc_sum=0;
        int t=0;
        char str1[20];
        while(isalnum(str[i]))
        {
            str1[t++]=str[i];
            asc_sum+=str[i];
            i+=1;
        }
        str1[t++]='\0';
        // printf("%s ",str1);
        for(int i=0;i<index;i++)
        {
            if(array[i].ascii_sum==asc_sum)
            {
                flag=!flag;
                array[i].frequency+=1;
            }
        }
        if(!flag)
        {
            strcpy((array[index].string),str1);
            array[index].ascii_sum=asc_sum;
            array[index].frequency+=1;
            index+=1;
        }
    }
    for(int i=0;i<MAX;i++)
    {
        if(array[i].ascii_sum>0 && array[i].frequency>1)
        {
            printf("\n%s = %d",array[i].string,array[i].frequency);
        }
    }
}