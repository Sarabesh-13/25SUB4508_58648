//program to create and use semaphore and store value using union
#include<sys/ipc.h>
#include<sys/sem.h>
#include<iostream>

using namespace std;

union semunion
{
    int value;
};

int main()
{
    key_t key=ftok("/home/student/25SUB4508_58648/Classwork/Day24/semfile",70);
    int semid=semget(key,4,IPC_CREAT|0666);
    union semunion args;
    semctl(semid,0,SETVAL,args);
    sembuf sb ={0,-1,0};
    semop(semid,&sb,1);
    cout<<"critical section"<<endl;
    sb.sem_op=1;
    semop(semid,&sb,1);
    semctl(semid,4,IPC_RMID,nullptr);
    return 0;
}