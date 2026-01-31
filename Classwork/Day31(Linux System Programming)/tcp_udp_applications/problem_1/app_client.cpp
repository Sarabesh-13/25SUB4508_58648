#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

#define PORT 9090
#define BUFFER 1024

class ATMClient
{
private:
    int sock;
    sockaddr_in server_addr{};

public:
    ATMClient()
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    }

    bool connectToServer()
    {
        return connect(sock, (sockaddr *)&server_addr, sizeof(server_addr)) == 0;
    }

    void verifyAccount(const string &acc)
    {
        string req = "VERIFY " + acc;
        write(sock, req.c_str(), req.size());

        char buf[BUFFER]{};
        int n = read(sock, buf, BUFFER - 1);
        if (n > 0)
        {
            buf[n] = '\0';
            cout << "Server response: " << buf;
        }
    }

    ~ATMClient()
    {
        close(sock);
    }
};

int main()
{
    ATMClient client;

    if (!client.connectToServer())
    {
        cerr << "Failed to connect to server\n";
        return 1;
    }

    string acc;
    cout << "Enter account number to verify: ";
    cin >> acc;

    client.verifyAccount(acc);
    return 0;
}