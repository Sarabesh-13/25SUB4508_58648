#include "ChatClient.h"
#include <iostream>
#include <cstring>
#include <sys/select.h>
#include <unistd.h>
#include <arpa/inet.h>

ChatClient::ChatClient(int serverPort) : port(serverPort)
{
    memset(&serverAddr, 0, sizeof(serverAddr));
}

bool ChatClient::initialize()
{
    if (!socket.createSocket())
    {
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    std::cout << "UDP Chat Client started\n";
    std::cout << "Type your messages:\n";
    return true;
}

void ChatClient::handleUserInput()
{
    char msg[BUFFER_SIZE];
    std::cin.getline(msg, BUFFER_SIZE);

    if (strlen(msg) > 0)
    {
        socket.sendTo(msg, strlen(msg), serverAddr);
    }
}

void ChatClient::handleServerMessage()
{
    char buffer[BUFFER_SIZE];
    sockaddr_in dummy{};
    ssize_t n = socket.receiveFrom(buffer, BUFFER_SIZE - 1, dummy);

    if (n > 0)
    {
        buffer[n] = '\0';
        std::cout << "\r" << buffer << std::endl;
        std::cout.flush();
    }
}

void ChatClient::run()
{
    fd_set readfds;
    int sockfd = socket.getSocket();
    int maxfd = sockfd > STDIN_FILENO ? sockfd : STDIN_FILENO;

    while (true)
    {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(sockfd, &readfds);

        select(maxfd + 1, &readfds, nullptr, nullptr, nullptr);

        // Handle server messages first to avoid input/output mixing
        if (FD_ISSET(sockfd, &readfds))
        {
            handleServerMessage();
        }

        // Handle user input
        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            handleUserInput();
        }
    }
}
