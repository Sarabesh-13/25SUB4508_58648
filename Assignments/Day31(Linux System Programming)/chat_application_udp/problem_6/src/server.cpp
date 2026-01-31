#include "ChatServer.h"
#include <iostream>

#define PORT 4003

int main() {
    ChatServer server(PORT);
    
    if (!server.initialize()) {
        std::cerr << "Failed to initialize server\n";
        return 1;
    }
    
    server.run();
    
    return 0;
}
