/*
Task-8
File Operation in C
*/

#include<stdio.h>
#include<stdlib.h>

#define MAX 99

int main()
{
    FILE* fp=NULL;
    char buffer[99];
    fp=fopen("data.txt","w+");
    if(fp==NULL)
    {
        perror("Error opening the file\n");
        exit(EXIT_SUCCESS);
    }
    fprintf_s(fp,"%s","Hello,File Handling in C!");
    printf("File pointer is at %ld\n",ftell(fp));
    fflush(fp);
    rewind(fp);
    printf("File pointer is at %ld\n",ftell(fp));
    if(fgets(buffer,sizeof(buffer),fp)!=NULL)
    {
        printf("%s\n",buffer);
    }
    fclose(fp);
    return 0;
}