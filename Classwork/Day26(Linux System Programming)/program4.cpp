//program to demonstrate shared memory using class object
#include<sys/ipc.h>
#include<sys/shm.h>
#include<cstring>
#include<iostream>

using namespace std;

class Employee
{
    int id;
    string name;
    public:
    // Employee(int i,string& n): id(i),name(n) {}
    void setValues(int i, string& n) {id = i; name=n;}
    void disp()
    {
        cout<<"id:"<<id<<endl;
        cout<<"name:"<<name<<endl;
    }
    ~Employee()=default;
};

int main()
{
    key_t key=ftok("/home/student/25SUB4508_58648/Classwork/Day24/progfile2",65);
    if(key==-1)
    {
        perror("key failure");
        return 1;
    }
    int shmid=shmget(key,1024,IPC_CREAT|0666);
    if(shmid==-1)
    {
        perror("shared memory create failure");
        return 1;
    }
    Employee* e =(Employee*)shmat(shmid,(void*)NULL,0);
    string n="varun";
    e->setValues(12,n);
    e->disp();
    shmdt(e);
    return 0;
}