//program demonstrating execl() system call in C++
#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

using namespace std;

int main()
{
    execl("/home/student/programs/prog6","program6",(char*)0);
    return 0;
}