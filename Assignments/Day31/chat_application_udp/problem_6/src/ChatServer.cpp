#include "ChatServer.h"
#include <iostream>
#include <cstring>

ChatServer::ChatServer(int serverPort)
    : nextClientId(1), port(serverPort)
{
}

bool ChatServer::initialize()
{
    if (!socket.createSocket())
    {
        return false;
    }

    if (!socket.bindSocket("127.0.0.1", port))
    {
        return false;
    }

    std::cout << "UDP Chat Server running on port " << port << std::endl;
    return true;
}

int ChatServer::findOrCreateClient(const sockaddr_in &sender)
{
    // Check if client already exists
    for (const auto &client : clients)
    {
        if (client.isSameClient(sender))
        {
            return client.getId();
        }
    }

    // Create new client
    int newId = nextClientId++;
    clients.emplace_back(sender, newId);
    std::cout << "Client " << newId << " joined\n";
    return newId;
}

void ChatServer::broadcastMessage(int senderId, const std::string &message)
{
    char formattedMsg[BUFFER_SIZE];
    snprintf(formattedMsg, BUFFER_SIZE, "Client %d: %.900s", senderId, message.c_str());

    for (const auto &client : clients)
    {
        if (client.getId() != senderId)
        {
            socket.sendTo(formattedMsg, strlen(formattedMsg), client.getAddress());
        }
    }
}

void ChatServer::run()
{
    char buffer[BUFFER_SIZE];

    while (true)
    {
        sockaddr_in sender{};
        ssize_t n = socket.receiveFrom(buffer, BUFFER_SIZE - 1, sender);

        if (n <= 0)
        {
            continue;
        }

        buffer[n] = '\0';

        int senderId = findOrCreateClient(sender);
        std::cout << "Client " << senderId << ": " << buffer << std::endl;

        broadcastMessage(senderId, buffer);
    }
}
