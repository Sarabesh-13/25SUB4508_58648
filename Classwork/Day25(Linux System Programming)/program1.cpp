//program to get process id and parent process id
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

using namespace std;

int main()
{
    pid_t p1=getpid();
    pid_t p2=getppid();
    cout<<"child process id:"<<p1<<endl;
    cout<<"parent process id:"<<p2<<endl;
    return 0;
    
}