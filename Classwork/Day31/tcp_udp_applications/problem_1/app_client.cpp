// app_client.cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 9090
#define BUFFER 1024

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(sock, (sockaddr*)&addr, sizeof(addr));

    string acc;
    cout << "Enter account number to verify: ";
    cin >> acc;

    string req = "VERIFY " + acc;
    write(sock, req.c_str(), req.size());

    char buf[BUFFER]{};
    int n = read(sock, buf, BUFFER - 1);
    if (n > 0) {
        buf[n] = '\0';
        cout << "Server response: " << buf;
    }

    close(sock);
}
