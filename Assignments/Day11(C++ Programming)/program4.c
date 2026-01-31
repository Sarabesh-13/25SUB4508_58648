// program for remove all characters in second string which are in first string

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX 256

int main()
{
    char str1[MAX];
    char str2[MAX];
    printf("Enter first string 1: ");
    fgets(str1,sizeof(str1),stdin);
    printf("\nEnter second string 2: ");
    fgets(str2,sizeof(str2),stdin);
    int visited[MAX];
    for(int i=0;i<MAX;i++)
    {
        visited[i]=false;
    }
    for(int i=0;i<strlen(str1);i++)
    {
        if(str1[i]>=48 && str1[i]<=57)
        {
            int num_pos=str1[i];
            // printf("%c %d\n",str1[i],num_pos);
            if(visited[num_pos]!=true)
            {
                visited[num_pos]=true;
            }
        }
        else if(str1[i]>=97 && str1[i]<=122)
        {
            int A_pos=str1[i];
            // printf("%c %d\n",str1[i],A_pos);
            if(visited[A_pos]!=true)
            {
                visited[A_pos]=true;
            }
        }
        else if(str1[i]>=65 && str1[i]<=90)
        {
            int a_pos=str1[i];
            // printf("%c %d\n",str1[i],a_pos);
            if(visited[a_pos]!=true)
            {
                visited[a_pos]=true;
            }
        }
    }
    for(int i=0;i<strlen(str2);i++)
    {
        if(visited[str2[i]]==true)
        {
            continue;
        }
        else
        {
            printf("%c",str2[i]);
        }
    }
    
    return 0;
}