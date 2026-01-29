#include "ChatClient.h"
#include <iostream>

#define PORT 4003

int main() {
    ChatClient client(PORT);
    
    if (!client.initialize()) {
        std::cerr << "Failed to initialize client\n";
        return 1;
    }
    
    client.run();
    
    return 0;
}
