//program to handle SIGCHLD signal using sigaction and reap the zombie process
#include<csignal>
#include<iostream>
#include<cstring>
#include<sys/wait.h>
#include<unistd.h>

using namespace std;

void sig_handler(int sig)
{
    cout<<"Signal:"<<sig<<endl;
    while(waitpid(-1,nullptr,WNOHANG)>0);
}



int main()
{
    struct sigaction sa;
    memset(&sa,0,sizeof(sa));
    sa.sa_handler=sig_handler;
    sa.sa_flags=SA_RESTART;
    sigaction(SIGCHLD,&sa,nullptr);

    if(fork()==0)
    {
        cout<<"cHILD PID:"<<getpid()<<endl;
        exit(0);
    }
    while(1)
    {
        cout<<"pARENT PID:"<<getpid()<<endl;
        sleep(1);
    }
    return 0;
}