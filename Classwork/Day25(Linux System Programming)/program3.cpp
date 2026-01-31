//program to demonstrate wait() system call in C++
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

using namespace std;

int main()
{
    pid_t p1;
    p1=fork();
    if(p1==0)
    {
        // cout<<"Child process"<<endl;
        for(int i=0;i<10;i++)
        {
            cout<<"child process[" <<i<<"]"<<endl;
            sleep(1);
        }
    }
    else
    {
        // cout<<"parent process"<<endl;
        wait(NULL);
        for(int i=0;i<10;i++)
        {
            cout<<"parent process[" <<i<<"]"<<endl;
            sleep(1);
        }
    }
    return 0;
}