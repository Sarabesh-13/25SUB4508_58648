/*

sender.cpp for demonstrating inter-process communication using POSIX pipes.
This program creates a pipe, forks a child process, and sends a message from the parent to the child.
here unamed_pipe cannot have sender and receiver in different files as it is not persistent like named pipes.

*/
#include <iostream>
#include <unistd.h>
#include <cstring>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) { 
        close(fd[1]);
        char buf[100];
        read(fd[0], buf, sizeof(buf));
        std::cout << "Receiver: " << buf << std::endl;
        close(fd[0]);
    } 
    else { 
        close(fd[0]);
        const char* msg = "Hello from pipe sender";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }
    return 0;
}
