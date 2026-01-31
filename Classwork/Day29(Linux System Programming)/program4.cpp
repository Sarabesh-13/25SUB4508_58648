/*
program to implement TCP/IP server using oops concept and use fork() 
process call to handle multiple clients.
*/
#include <iostream>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <vector>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>


#define BUFFER_SIZE 1024
#define PORT 4003

using namespace std;

class SocketException: public runtime_error
{
    public:
        explicit SocketException(const string &msg): runtime_error(msg){}
        
};


class ClientHandler
{
public:
    static void handleClient(int client_fd){
        char buffer[BUFFER_SIZE];
        cout<<"[Thread "<<this_thread::get_id()<<" ] Client connected\n";

        while(true)
        {
            memset(buffer, 0, BUFFER_SIZE);
            ssize_t bytes = read(client_fd, buffer, BUFFER_SIZE);
            if(bytes <=0)
            {
                cout<<"[Thread "<<this_thread::get_id()<<" ] Client disconnected"<<endl;
                break;
            }

            cout<<"[Client] : "<<buffer;
            string reply = "Server ACK: ";
            reply += buffer;
            write(client_fd, reply.c_str(), reply.size());

        }
        close(client_fd);
    }
};

class TCPThreadServer
{
private:
    int server_fd;
public:
    TCPThreadServer() : server_fd(-1){}
    ~TCPThreadServer(){
        if(server_fd != -1)
            close(server_fd);
    }

    void setup()
    {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(server_fd < 0)
            throw SocketException("Socket Creation Failed");
        
        int opt = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(PORT);

        if(bind(server_fd, (sockaddr *)&addr, sizeof(addr))<0)
            throw SocketException("Bind Failed");

        if(listen(server_fd, 10)<0)
            throw SocketException("Listen Failed");
        
        cout<<"Thread Server listening on port: "<<PORT<<endl;
    }


    void run()
    {
        while(true)
        {
            int client_fd = accept(server_fd, nullptr, nullptr);
            if(client_fd < 0)
                continue;
            //spawn a thread per client
            thread t(ClientHandler::handleClient, client_fd);
            t.detach();  // no join - auto cleanup
        }
    }
};

int main()
{
    try
    {
        TCPThreadServer server;
        server.setup();
        server.run();
    }
    catch(const SocketException e)
    {
        std::cerr<<"Server Error: " << e.what() << '\n';
    }
    
    return 0;
}

