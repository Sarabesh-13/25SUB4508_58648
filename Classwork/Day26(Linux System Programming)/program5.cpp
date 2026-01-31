//program to demonstrate race condition using shared memory
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>


using namespace std;


int main()
{
    key_t key = ftok("shm_race_demo", 75);
    int shmid = shmget(key, sizeof(int), IPC_CREAT| 0666);

    int *counter = (int *)shmat(shmid, nullptr, 0);
    *counter = 0;

    pid_t pid = fork();

    if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<10000000;i++)
    {
        (*counter)++;
    }

    if(pid == 0)
    {
        //child process
        shmdt(counter);
        return 0;
    }
    else
    {
        //parent process
        wait(nullptr);
        cout<<"\nFinal Counter: "<<*counter<<endl;
        cout<<"\nExpected Value: 20000000"<<endl;

        if(*counter != 20000000)
        {
            cout<<"\nResult: Race Condition Detected (Lost "
            <<20000000-*counter<<" )"<<endl;
        }

        shmdt(counter);
        shmctl(shmid, IPC_RMID, nullptr);
    }

    return 0;

}