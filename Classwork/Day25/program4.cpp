//program to demonstrate fork() and wait() system calls in C++
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

using namespace std;

int main()
{
    pid_t p1;
    p1=fork();
    if(p1<0)
    {
        cout<<"fork failure"<<endl;
        exit(0);
    }
    else if(p1==0)
    {
        cout<<"Child process"<<endl;
        cout<<"child ps id:"<<getpid()<<endl;
        cout<<"child exiting"<<endl;
        exit(0);
    }
    else
    {
        cout<<"parent process"<<endl;
        cout<<"parent ps id:"<<getpid()<<endl;
        sleep(30);
        cout<<"parent exiting"<<endl;
        
    }
    return 0;
}