#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>

class UDPSocket {
private:
    int sockfd;
    sockaddr_in addr;

public:
    UDPSocket();
    ~UDPSocket();
    
    bool createSocket();
    bool bindSocket(const std::string& ip, int port);
    ssize_t sendTo(const char* data, size_t len, const sockaddr_in& dest);
    ssize_t receiveFrom(char* buffer, size_t len, sockaddr_in& sender);
    int getSocket() const { return sockfd; }
    void closeSocket();
};

#endif
