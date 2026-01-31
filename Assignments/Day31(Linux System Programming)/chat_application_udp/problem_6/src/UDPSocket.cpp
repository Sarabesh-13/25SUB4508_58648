#include "UDPSocket.h"
#include <unistd.h>
#include <cstring>
#include <iostream>

UDPSocket::UDPSocket() : sockfd(-1) {
    memset(&addr, 0, sizeof(addr));
}

UDPSocket::~UDPSocket() {
    closeSocket();
}

bool UDPSocket::createSocket() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return false;
    }
    return true;
}

bool UDPSocket::bindSocket(const std::string& ip, int port) {
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    
    if (bind(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return false;
    }
    return true;
}

ssize_t UDPSocket::sendTo(const char* data, size_t len, const sockaddr_in& dest) {
    return sendto(sockfd, data, len, 0, (sockaddr*)&dest, sizeof(dest));
}

ssize_t UDPSocket::receiveFrom(char* buffer, size_t len, sockaddr_in& sender) {
    socklen_t senderLen = sizeof(sender);
    return recvfrom(sockfd, buffer, len, 0, (sockaddr*)&sender, &senderLen);
}

void UDPSocket::closeSocket() {
    if (sockfd >= 0) {
        close(sockfd);
        sockfd = -1;
    }
}
