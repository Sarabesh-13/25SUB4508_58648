#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>

class Client {
private:
    sockaddr_in addr;
    int id;

public:
    Client(const sockaddr_in& address, int clientId);
    
    const sockaddr_in& getAddress() const { return addr; }
    int getId() const { return id; }
    
    bool isSameClient(const sockaddr_in& other) const;
};

#endif
