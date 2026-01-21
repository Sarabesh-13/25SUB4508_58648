// Task-11 read from shared memory from another process 

#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>

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
    char* s1=(char*)shmat(shm_id,(void*)0,0);
    cout<<"Data readed from shared memory:"<<s1<<endl;
    shmdt(s1);
    return 0;
}