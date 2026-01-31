//implementation of tcp/ip server connection using oops concept.
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdexcept>
#include <exception>

#define BACKLOG 5
#define BUFFERSIZE 1024

using namespace std;

class SocketException : public runtime_error
{
    const char *str = nullptr;

public:
    explicit SocketException(const string &msg) : runtime_error(msg) {}
};

class TCPServer
{
private:
    int server_fd;
    int port;

public:
    explicit TCPServer(int port) : server_fd(-1), port(port) {}
    ~TCPServer()
    {
        if (server_fd != -1)
        {
            close(server_fd);
        }
    }
    void createSocket()
    {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0)
        {
            throw SocketException("Socket creation failed");
        }
    }
    void bindSocket()
    {
        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            throw("Bind failed");
        }
    }

    void listenSocket()
    {
        if (listen(server_fd, BACKLOG) < 0)
        {
            throw SocketException("listen failed");
        }
    }

    void start()
    {
        createSocket();
        bindSocket();
        listenSocket();

        cout << "Server listening on port:" << port << endl;
        signal(SIGCHLD, SIG_IGN); // prevent zombies

        while (true)
        {
            sockaddr_in client_addr{};
            socklen_t client_len = sizeof(client_addr);

            int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
            if (client_fd < 0)
            {
                continue;
            }
            pid_t p = fork();
            if (p == 0)
            {
                close(server_fd);
                handleClient(client_fd);
                exit(EXIT_SUCCESS);
            }
            else if (p > 0)
            {
                close(client_fd);
            }
            else
            {
                cerr << "fork failed:" << endl;
                close(client_fd);
            }
        }
    }

    void handleClient(int client_fd)
    {
        char buffer[client_fd];
        ssize_t bytes_read;
        while (true)
        {
            memset(buffer, '\0', BUFFERSIZE);
            bytes_read = read(client_fd, buffer, BUFFERSIZE);
            if (bytes_read <= 0)
            {
                cout << "Client got disconnected (PID " << getpid() << ")" << endl;
                break;
            }
            cout << "Client [" << getpid() << "]: " << buffer << endl;
            string respose = "Server ACK:";
            respose += buffer;
            write(client_fd, respose.c_str(), respose.size());
        }
        close(client_fd);
    }
};

int main()
{
    try
    {
        TCPServer server(4003);
        server.start();
    }
    catch (const SocketException &e)
    {
        cerr << "Server error: " << endl;
        cerr << e.what() << endl;
    }
}