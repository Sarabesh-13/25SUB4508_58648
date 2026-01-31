//receiver.cpp for reading from a named pipe (FIFO)
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char* fifo = "/tmp/my_fifo";

    char buf[100];
    int fd = open(fifo, O_RDONLY);
    read(fd, buf, sizeof(buf));
    std::cout << "Receiver: " << buf << std::endl;
    close(fd);
    return 0;
}
