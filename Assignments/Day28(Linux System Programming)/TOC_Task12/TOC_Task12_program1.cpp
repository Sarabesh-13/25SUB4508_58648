// implementation of simple tcp/ip client connection using sockets.
//Task 12
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#define PORT 4003
#define MAXBUFF 1024

using namespace std;

int main()
{
    int sd, rVal = 0;

    struct sockaddr_in serv_addr;

    char msg[MAXBUFF] = {'\0',};

    sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    cout << "[server] socket created with sd: " << sd << endl;

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);                   // server's port no
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // server's ipaddr

    rVal = connect(sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    // rVal = bind(sd,(struct sockaddr *) &serv_addr,  sizeof(serv_addr));

    if (rVal < 0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    cout << "[client] connected to server with ipaddr: 127.0.0.1 port: 4003 is done!" << endl;

    memset(msg, '\0', MAXBUFF);
    read(sd, msg, MAXBUFF);
    cout << "\n[client]:\n\n"
         << msg << endl;

    memset(msg, '\0', MAXBUFF);
    cout << "\nMessage: ";
    cin.getline(msg, MAXBUFF);
    // strcpy(msg,"Hi from the client\n");
    write(sd, msg, strlen(msg));
    cout << "\nSending message to the server: " << msg << endl;
    memset(msg, 0, MAXBUFF);
    read(sd, msg, MAXBUFF);
    cout << "\n[server reply]: " << msg << endl;
    close(sd);

    return 0;
}
