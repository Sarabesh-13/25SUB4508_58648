#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<iostream>
#include <mqueue.h>
#include <string.h>

#define MQ_NAME "/posix1_mq"

int main() {
    mqd_t mq = mq_open(MQ_NAME, O_WRONLY);
    if (mq == -1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    const char* str = "Hello POSIX IPC!";
    if (mq_send(mq, str, strlen(str) + 1, 0) == -1)
    {
        perror("mq_send");
        exit(EXIT_FAILURE);
    }

    mq_close(mq);
    return 0;
}
