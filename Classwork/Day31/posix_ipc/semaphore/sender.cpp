#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define SEM_NAME "/my_posix_sem"

int main() {
    sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);

    std::cout << "Sender: Doing some work...\n";
    sleep(2);

    std::cout << "Sender: Signaling receiver\n";
    sem_post(sem);

    sem_close(sem);
    return 0;
}
