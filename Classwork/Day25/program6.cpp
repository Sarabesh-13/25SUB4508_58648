//demo program used by another process to demonstrate exec() system call in C++
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

using namespace std;

int main()
{
    cout<<"Hello World"<<endl;
    return 0;
}