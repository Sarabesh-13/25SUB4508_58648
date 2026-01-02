#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<string.h>

#define print(a,b) printf("%d %d",a,b);

int main()
{
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
  return 0;
}

