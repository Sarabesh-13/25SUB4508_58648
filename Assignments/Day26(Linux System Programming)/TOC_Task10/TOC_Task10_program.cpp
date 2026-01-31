/*
Task-10
C program for process creation and management
use fork to create child process,In child process execute an external program
*/
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

using namespace std;

int main()
{
    pid_t p1;
    if(p1==0)
    {
      cout<<"executing ls cmd with execvp"<<endl;
      char* args[]={"ls","-lia","home/student/programs"};
      execvp("/bin/ls",args);
      exit(EXIT_SUCCESS);
      cout<<"executed cmd ls -lia"<<endl; //line will not execute
    }
    else
    {
      wait(nullptr);
      cout<<"Child process completed it's execution"<<endl;
    }
}