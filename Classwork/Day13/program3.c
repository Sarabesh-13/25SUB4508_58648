#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<string.h>

#define print(a,b) printf("%d %d",a,b);

typedef struct Employee
{
    char name[20];
    int id;
    char gender;
    int salary;
    
}Emp;

void disp(const Emp e);

int main()
{
  Emp emp;
  FILE* fp=fopen("/home/student/programs/file.txt","r");
  char str[20];
  if(fp==NULL)
  {
    printf("file not found\n");
    exit(EXIT_FAILURE);
  }
  memset(str,'\0',sizeof(str));
  fscanf(fp,"%[^\n]",str);
  fprintf(stdout,"\n%s\n",str);
  fclose(fp);
  char* token=strtok(str,"|");
  return 0;
}