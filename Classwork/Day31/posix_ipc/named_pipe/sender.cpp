#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

int main() {
    const char* fifo = "/tmp/my_fifo";
    mkfifo(fifo, 0666);

    int fd = open(fifo, O_WRONLY);
    const char* msg = "Hello from FIFO sender";
    write(fd, msg, strlen(msg) + 1);
    close(fd);
    return 0;
}
