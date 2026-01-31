//program for inter process communication using pipe in C++
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<cstring>

using namespace std;

int main()
{
    int p_fd[2];
    pipe(p_fd); //once created one used for file type and file descriptor is created that is one for read and another for write
    pid_t cpid;
    cpid=fork();
    char buff_r[1024]={'\0',};
    char buff_w[1024]={'\0',};
    strcpy(buff_w,"\nThis is a cpp file\n");
    if(cpid<0)
    {
        perror("fork failure");
        return 1;
    }
    else if(cpid==0)
    {
       //child process
        write(p_fd[1],buff_w,strlen(buff_w));

    }
    else{
       //parent process
        wait(0);
        read(p_fd[0],buff_r,sizeof(buff_r));
        cout<<"Read buffer:"<<buff_r<<endl;
    }
}