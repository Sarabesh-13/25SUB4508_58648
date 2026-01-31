//program to handle SIGCHLD signal using sigaction and use restart flag and restore older signal action
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
    struct sigaction sa,old_sa;
    memset(&sa,0,sizeof(sa));
    memset(&old_sa,0,sizeof(old_sa));
    sa.sa_handler=sig_handler;
    sa.sa_flags=SA_RESTART;
    sigaction(SIGINT,&sa,&old_sa);
    sigaction(SIGINT,&old_sa,nullptr); //restoring to older sigint actions
    sleep(5);
    write(1,"Handler is restored but it is not",42);
    while(1) pause();
    return 0;
}