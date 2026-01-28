//receiver.cpp for receiving data from shared memory using POSIX IPC
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

#define SHM_NAME "/my_shm"
#define SEM_NAME "/my_sem"
#define SIZE 1024

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    char* shm_ptr = (char*)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    sem_t* sem = sem_open(SEM_NAME, 0);

    sem_wait(sem);
    std::cout << "Received: " << shm_ptr << std::endl;

    munmap(shm_ptr, SIZE);
    close(shm_fd);

    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);
}
