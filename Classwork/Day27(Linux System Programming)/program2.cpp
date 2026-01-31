//program to handle multiple signals using signal() from csignal
#include <iostream>
#include <csignal>
#include <cstring>
#include <unistd.h>

using namespace std;


void display()
{
    cout<<"\n==================================\n";
    cout<<"\n==========CPP Programming=========\n";
    cout<<"\n==================================\n";
}

void sigFunctions(int sigNo)
{
    cout<<"\nSignal caught with number: "<<sigNo<<endl;
    if(sigNo == 8)
    {
        cout<<"\nDivide by zero Error"<<endl;
        _exit(EXIT_FAILURE);
    }
    else if(sigNo == 11)
    {
        cout<<"\nAllocate the space/memory first and then use it"<<endl;
        _exit(EXIT_FAILURE);
    }
    else if(sigNo == 2)
    {
        display();
    }
    
    else if(sigNo == 19)
    {
        cout<<"\nYour Prog is running in the background ";
        cout<<"\n with pid: "<<getpid()<<endl;
    }
    else if(sigNo == SIGCHLD)
    {
        cout<<"\nSignal is passed to the child\n";
        cout<<"\n with pid: "<<getpid()<<endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout<<"\nUnCaught Signal\n";
    }

}


int main()
{
    int a=10,b=0;
    int z;
    char *ptr;
    signal(SIGINT, sigFunctions);
    signal(SIGFPE, sigFunctions);
    signal(SIGSEGV, sigFunctions);
    //signal(SIGSTOP, sigFunctions);
    signal(SIGCHLD, sigFunctions);
    signal(SIGHUP, sigFunctions);
    
    // z = a/b;

    // cout<<"\nz="<<z<<endl;
    //strcpy(ptr,"bhima");
    //cout<<"ptr: "<<*ptr<<endl;
    //while(1);
    pid_t cpid = fork();
    if(cpid == 0)
    {
        sleep(30);
        exit(EXIT_FAILURE);

    }
    else{
        while(1){ cout<<"\n[parent] "<<getpid()<<endl;
        sleep(3);
        }
    }
    cout<<"\nProgram ended"<<endl;
    return 0;
}