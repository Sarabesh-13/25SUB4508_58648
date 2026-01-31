//program to demonstrate character input and output until newline or EOF usinf getchar() and putchar()

#include<stdio.h>
#include<stdlib.h>
int main()
{
char ch;
while((ch=getchar())!='\n' && ch!=EOF)
{
    putchar(ch);
} 
return 0;
}