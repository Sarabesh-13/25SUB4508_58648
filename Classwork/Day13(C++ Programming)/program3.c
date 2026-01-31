//program for getting file data into structure in c.
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<string.h>

#define print(a,b) printf("%d %d",a,b)

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
  strcpy(emp.name,token);
  token=strtok(NULL,"|");
  emp.id=atoi(token);
  token=strtok(NULL,"|");
  emp.gender=token[0];
  token=strtok(NULL,"|");
  emp.salary=atoi(token);
  disp(emp);
  return 0;
}

void disp(const Emp e)
{
    printf("Name:%s\n",e.name);
    printf("ID:%d\n",e.id);
    printf("Gender:%c\n",e.gender);
    printf("Salary:%d\n",e.salary);
}