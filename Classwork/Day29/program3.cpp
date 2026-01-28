/*
implementation of tcp/ip client connection using oops concept 
and select() function to handle I/O multiplexing.
*/
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdexcept>

#define PORT 8080
#define BUFFER_SIZE 1024

// custom exception handling
using namespace std;

class SocketException : public runtime_error
{
public:
    explicit SocketException(const string &msg) : runtime_error(msg) {}
};

class TCPSelectClient
{
private:
    int sock_fd;

public:
    TCPSelectClient() : sock_fd(-1) {}
    ~TCPSelectClient()
    {
        if (sock_fd != -1)
            close(sock_fd);
    }

    void connectToServer(const string &ip)
    {
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_fd < 0)
        {
            throw SocketException("Socket creation failed");
        }

        sockaddr_in serv{};
        serv.sin_family = AF_INET;
        // server_addr.sin_addr.s_addr = INADDR_ANY;
        serv.sin_port = htons(PORT);
        if (inet_pton(AF_INET, ip.c_str(), &serv.sin_addr) < 0)
        {
            throw SocketException("Invalid Server IP");
        }
        cout << "Connected to the server" << endl;
    }

    void run()
    {
        fd_set readfds;
        char buffer[BUFFER_SIZE];

        while (true)
        {
            FD_ZERO(&readfds);
            FD_SET(STDIN_FILENO, &readfds);
            FD_SET(sock_fd, &readfds);

            int maxfd = std::max(STDIN_FILENO, sock_fd);

            int ret = select(maxfd + 1, &readfds, nullptr, nullptr, nullptr);

            if (ret < 0)
                throw SocketException("select() failed");

            // keyboard activity
            if (FD_ISSET(STDIN_FILENO, &readfds))
            {
                memset(buffer, 0, BUFFER_SIZE);
                if (!fgets(buffer, BUFFER_SIZE, stdin))
                    break;
                if (strncmp(buffer, "exit", 4) == 0)
                    break;
                write(sock_fd, buffer, strlen(buffer));
            }

            // server sent data
            if (FD_ISSET(sock_fd, &readfds))
            {
                memset(buffer, 0, BUFFER_SIZE);
                int bytes = read(sock_fd, buffer, BUFFER_SIZE);
                if (bytes <= 0)
                {
                    cout << "Server closed connection" << endl;
                    break;
                }
                cout << "Server: " << buffer << endl;
            }
        }
    }
};

int main()
{

    try
    {
        TCPSelectClient client;
        client.connectToServer("127.0.0.1");
        client.run();
    }
    catch (const SocketException &ex)
    {
        cerr << "Client error: " << ex.what() << endl;
    }

    return 0;
}