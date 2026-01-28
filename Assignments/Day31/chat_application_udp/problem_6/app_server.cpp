// app_server.cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 4003
#define BUFFER_SIZE 1024

using namespace std;

struct Client {
    sockaddr_in addr;
    int id;
};

bool sameClient(const sockaddr_in &a, const sockaddr_in &b) {
    return a.sin_addr.s_addr == b.sin_addr.s_addr &&
           a.sin_port == b.sin_port;
}

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    if (bind(sockfd, (sockaddr*)&server, sizeof(server)) < 0) {
        perror("bind");
        return 1;
    }

    cout << "UDP Chat Server running on port " << PORT << endl;

    vector<Client> clients;
    int nextClientId = 1;

    while (true) {
        char buffer[BUFFER_SIZE];
        sockaddr_in sender{};
        socklen_t len = sizeof(sender);

        ssize_t n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                             (sockaddr*)&sender, &len);
        if (n <= 0) continue;

        buffer[n] = '\0';

        // Check if sender already exists
        int senderId = -1;
        for (auto &c : clients) {
            if (sameClient(c.addr, sender)) {
                senderId = c.id;
                break;
            }
        }

        // New client
        if (senderId == -1) {
            senderId = nextClientId++;
            clients.push_back({sender, senderId});
            cout << "Client " << senderId << " joined\n";
        }

        cout << "Client " << senderId << ": " << buffer << endl;

        // Prepare broadcast message
        char msg[BUFFER_SIZE];
        snprintf(msg, BUFFER_SIZE, "Client %d: %.900s", senderId, buffer);

        for (auto &c : clients)
        {
            if (c.id != senderId)
            {
                sendto(sockfd, msg, strlen(msg), 0,
                       (sockaddr *)&c.addr, sizeof(c.addr));
            }
        }
    }
    close(sockfd);
    return 0;
}

/*

Sample Output:

UDP Chat Server running on port 4003
Client 1 joined
Client 1: Hello from client 1
Client 2 joined
Client 2: Hi there, client 1!

the above output will be generated on server console when clients connect and send messages.
also if a client sends an empty message, it will not be broadcasted and mesage from one client will not be shown on its own console.
we have also prefferred udp over tcp for this chat application because udp is faster and more efficient for real-time communication like chat applications 
where occasional packet loss is acceptable.also udp has lower latency compared to tcp which is crucial for chat applications.

*/