// app_client.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#define PORT 4003
#define BUFFER_SIZE 1024
using namespace std;

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }
    
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    
    cout << "UDP Chat Client started\n";
    cout << "Type your messages:\n";
    
    fd_set readfds;
    int maxfd = sockfd > STDIN_FILENO ? sockfd : STDIN_FILENO;
    
    while (true) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(sockfd, &readfds);
        
        select(maxfd + 1, &readfds, nullptr, nullptr, nullptr);
        
        // Receive broadcast first (to avoid input/output mixing)
        if (FD_ISSET(sockfd, &readfds)) {
            char buffer[BUFFER_SIZE];
            ssize_t n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, nullptr, nullptr);
            if (n > 0) {
                buffer[n] = '\0';  // Null-terminate
                cout << "\r" << buffer << endl;  // \r clears current line
                cout.flush();
            }
        }
        
        // Send
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            char msg[BUFFER_SIZE];
            cin.getline(msg, BUFFER_SIZE);
            if (strlen(msg) > 0) 
            {  
                sendto(sockfd, msg, strlen(msg), 0,
                       (sockaddr*)&server, sizeof(server));
            }
        }
    }
    
    close(sockfd);
    return 0;
}