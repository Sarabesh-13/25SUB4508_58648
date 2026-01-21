/*
Task-11 IPC using shared memory
create a shared memory segment and attach to process memory space and write a string message in shared memory in one process and 
read it in another process
*/

#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<cstring>

using namespace std;

int main()
{
    key_t key=ftok("/home/student/25SUB4508_58648/Classwork/Day24/shfile",62);
    if(key==-1)
    {
        perror("Failed to generate key");
        return 1;
    }
    int shm_id=shmget(key,1024,IPC_CREAT|0666);
    if(shm_id==-1)
    {
        perror("Failed to generate shared memory");
        return 1;
    }
    char* k=(char*)shmat(shm_id,(void*)0,0);
    string s="hello world";
    strncpy(k,s.c_str(),1024);
    cout<<"Data written to shared memory"<<endl;
    shmdt(k);
    return 0;
}