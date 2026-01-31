//program to create a semaphore with 4 segments and initialize their values
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>


using namespace std;


int main()
{
    key_t key = ftok("/home/student/25SUB4508_58648/Classwork/Day24/progfile3", 69);
    if(key==-1)
    {
        perror("key failure");
        return 1;
    }
    int sem=4;
    int sem_id = semget(key, sem, IPC_CREAT| 0666);
    if(sem_id==-1)
    {
        perror("semaphore failure");
        return 1;
    }
    int sem_val=semctl(sem_id,0,SETVAL,1001);
    sem_val=semctl(sem_id,1,SETVAL,1002);
    sem_val=semctl(sem_id,2,SETVAL,1003);
    sem_val=semctl(sem_id,3,SETVAL,1004);
    cout<<"semaphore created"<<endl;
    cout<<"semaphore segments:"<<sem<<endl;
    cout<<"semaphore id:"<<sem_id<<endl;
    return 0;

}