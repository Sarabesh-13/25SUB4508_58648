#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

#define SEM_NAME "/my_posix_sem"

int main() {
    sem_t* sem = sem_open(SEM_NAME, 0);

    std::cout << "Receiver: Waiting...\n";
    sem_wait(sem);

    std::cout << "Receiver: Got signal from sender\n";

    sem_close(sem);
    sem_unlink(SEM_NAME);
    return 0;
}
