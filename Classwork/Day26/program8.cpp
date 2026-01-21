//program to get all values of a semaphore with 4 segments by using a unsigned short array
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
    ushort arr[4];
    int sem_val=semctl(sem_id,0,GETALL,arr);
    if(sem_val==-1)
    {
        perror("failed to get values");
        return 1;
    }
    for(int i=0;i<sem;i++)
    {
        cout<<"Sem 0 return:"<<arr[i]<<endl;
    }
    return 0;
}