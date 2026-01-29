#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include "UDPSocket.h"
#include <string>

class ChatClient {
private:
    static const int BUFFER_SIZE = 1024;
    UDPSocket socket;
    sockaddr_in serverAddr;
    int port;

    void handleUserInput();
    void handleServerMessage();

public:
    ChatClient(int serverPort);
    bool initialize();
    void run();
};

#endif
