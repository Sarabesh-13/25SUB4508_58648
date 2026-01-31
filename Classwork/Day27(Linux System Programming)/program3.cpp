//program to handle SIGTERM and SIGINT signals using sigaction
#include<csignal>
#include<iostream>
#include<cstring>
#include<unistd.h>

using namespace std;

void sigterm_handler(int sig)
{
    cout<<"SIGTERM signal recieved"<<endl;
}

void sigint_handler(int sig)
{
    cout<<"SIGINT signal recieved"<<endl;
}



int main()
{
    struct sigaction sa_t,sa_i;
    memset(&sa_t,0,sizeof(sa_t));
    memset(&sa_i,0,sizeof(sa_i));
    sa_t.sa_handler=sigterm_handler;
    sa_i.sa_handler=sigint_handler;
    sigaction(SIGTERM,&sa_t,nullptr);
    sigaction(SIGINT,&sa_i,nullptr);

    while(1)
    {
        cout<<"Processing "<<getpid()<<endl;
        sleep(1);
    }
    return 0;
}