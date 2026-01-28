#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

#define PORT 9090
#define BUFFER 1024

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(sock, (sockaddr*)&addr, sizeof(addr));

    char buf[BUFFER];
    std::string input;

    while (true) {
        int n = read(sock, buf, BUFFER - 1);
        if (n <= 0) break;
        buf[n] = '\0';
        std::cout << buf;

        std::getline(std::cin, input);
        input += "\n";
        write(sock, input.c_str(), input.size());
    }

    close(sock);
}
