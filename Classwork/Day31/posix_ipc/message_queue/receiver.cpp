#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <iostream>

#define MQ_NAME "/posix1_mq"

using namespace std;

int main() {
    mqd_t mq;
    struct mq_attr attr;

    mq = mq_open(MQ_NAME, O_RDONLY);
    if (mq == -1) {
        perror("mq_open");
        return 1;
    }

    mq_getattr(mq, &attr);

    char *buff = new char[attr.mq_msgsize];

    ssize_t n = mq_receive(mq, buff, attr.mq_msgsize, NULL);
    if (n == -1) {
        perror("mq_receive");
        return 1;
    }

    buff[n] = '\0';
    cout << "Msg Received: " << buff << endl;

    delete[] buff;
    mq_close(mq);
    return 0;
}
