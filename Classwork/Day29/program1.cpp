//program to handle multiple clients concurrently in tcp/ip server using fork() process call.
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define PORT 4003
#define MAXBUFF 1024

using namespace std;

int main()
{
    int sd, csd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t clientAddrLen;
    char msg[MAXBUFF];

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
    {
        perror("socket");
        return 1;
    }
    cout << "[server] socket created" << endl;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind");
        return 1;
    }
    cout << "[server] bind done" << endl;

    if (listen(sd, 5) < 0)
    {
        perror("listen");
        return 1;
    }
    cout << "[server] listening..." << endl;

    while (1)
    {
        clientAddrLen = sizeof(client_addr);
        csd = accept(sd, (struct sockaddr *)&client_addr, &clientAddrLen);

        if (csd < 0)
        {
            perror("accept");
            continue;
        }

        cout << "[server] client connected" << endl;

        if (fork() == 0) // child process
        {
            close(sd);
            memset(msg, 0, MAXBUFF);
            strcpy(msg, "\n===========================\n");
            strcat(msg, "==========Welcome==========\n");
            strcat(msg, "===========================\n");

            write(csd, msg, strlen(msg));

            memset(msg, 0, MAXBUFF);
            read(csd, msg, MAXBUFF);
            cout << "[client_s]: " << msg << endl;
            cout << "[client_r]:" << "[server]," << msg << endl;
            // memset(msg, 0, MAXBUFF);
            // strcpy(msg, "[client_r]: [server],");
            write(csd, msg, strlen(msg));

            close(csd);
            return 0;
        }

        close(csd); // parent closes client socket
    }

    close(sd);
    return 0;
}