//program to handle SIGINT using sigaction also demonstrating SA_RESTART flag
#include<csignal>
#include<iostream>
#include<cstring>
#include<unistd.h>

using namespace std;

void sigint_handler(int sig)
{
    cout<<"\nSIGNAL:"<<sig<<endl;
    cout<<"Sent by PID"<<endl;
}



int main()
{
    struct sigaction sa_i;
    memset(&sa_i,0,sizeof(sa_i));
    sa_i.sa_handler=sigint_handler;
    sa_i.sa_flags=SA_RESTART;
    sigaction(SIGINT,&sa_i,nullptr);

    char buff[100];
    read(STDIN_FILENO,buff,sizeof(buff));
    cout<<buff<<endl;
    return 0;
}