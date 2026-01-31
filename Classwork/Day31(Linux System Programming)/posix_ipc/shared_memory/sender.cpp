/*
sender.cpp for POSIX shared memory sender which writes a message to shared memory and 
signals the receiver using a semaphore.
*/
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstring>

#define SHM_NAME "/my_shm"
#define SEM_NAME "/my_sem"
#define SIZE 1024

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);

    char* shm_ptr = (char*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);

    std::string msg = "Hello from sender (shared memory)";
    strcpy(shm_ptr, msg.c_str());

    sem_post(sem);

    munmap(shm_ptr, SIZE);
    close(shm_fd);
}
