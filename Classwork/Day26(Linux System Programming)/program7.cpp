//program to read and display semaphore values
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
    int sem_val=semctl(sem_id,0,GETVAL,0);
    cout<<"Semaphore 0 returned:"<<sem_val<<endl;
    sem_val=semctl(sem_id,1,GETVAL,0);
    cout<<"Semaphore 0 returned:"<<sem_val<<endl;
    sem_val=semctl(sem_id,2,GETVAL,0);
    cout<<"Semaphore 0 returned:"<<sem_val<<endl;
    sem_val=semctl(sem_id,3,GETVAL,0);
    cout<<"Semaphore 0 returned:"<<sem_val<<endl;
    return 0;

}