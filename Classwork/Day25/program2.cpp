//program to make child process dead before the parent process
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

using namespace std;

int main()
{
    cout<<"System programming"<<endl;
    pid_t p3=fork(); //sigchld
    if(p3==0)
    {
        sleep(20);
        pid_t ch=getpid();
        pid_t ch1=getppid();

        cout<<"I am a child process"<<endl;
        cout<<"My pid id:"<<ch<<endl;
        cout<<"My parent ps id:"<<ch1<<endl;
    }
    else
    {
        pid_t p1 = getpid();
        pid_t p2 = getppid();
        cout << "I am a parent process" << endl;
        cout << "My pid id:" << p1 << endl;
        cout<< "Child ps id:"<<p3<<endl;
        cout << "My parent ps id:" << p2 << endl;
    }
    return 0;
    
}