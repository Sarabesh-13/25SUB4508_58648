//program to handle SIGTSTP signal(ctrl+z)
#include<signal.h>
#include<iostream>
#include<unistd.h>

using namespace std;

void handle_sigstp(int sig)
{
    cout<<"\n SIGSTP recieved ctrl+z\n"<<endl;
    exit(0);
}

int main()
{
    signal(SIGTSTP,handle_sigstp);
    while(1)
    {
        cout<<"Processing:"<<getpid()<<endl;
        sleep(2);
    }
    return 0;
}