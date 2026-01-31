#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include "UDPSocket.h"
#include "Client.h"
#include <vector>
#include <string>

class ChatServer {
private:
    static const int BUFFER_SIZE = 1024;
    UDPSocket socket;
    std::vector<Client> clients;
    int nextClientId;
    int port;

    int findOrCreateClient(const sockaddr_in& sender);
    void broadcastMessage(int senderId, const std::string& message);

public:
    ChatServer(int serverPort);
    bool initialize();
    void run();
};

#endif
