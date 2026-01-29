#include "Client.h"

Client::Client(const sockaddr_in& address, int clientId) 
    : addr(address), id(clientId) {}

bool Client::isSameClient(const sockaddr_in& other) const {
    return addr.sin_addr.s_addr == other.sin_addr.s_addr &&
           addr.sin_port == other.sin_port;
}
