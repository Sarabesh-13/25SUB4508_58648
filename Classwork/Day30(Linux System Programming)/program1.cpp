//program to implement UDP Fork Server
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
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


class UDPServer
{
private:
    int sockfd;
    sockaddr_in server_addr;
public:
    UDPServer() : sockfd(-1){
        createSocket();
        bindSocket();
    }
    ~UDPServer(){
        if(sockfd != -1)
            close(sockfd);
    }
private:
    void createSocket(){
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd < 0)
            throw SocketException("Socket Creation Failed");
        
    }

    void bindSocket()
    {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_addr.sin_port = htons(PORT);
        if(bind(sockfd, (sockaddr *)&server_addr, sizeof(server_addr))<0)
            throw SocketException("Bind Failed");


    }

    void handleCLient(){

        char buffer[BUFFER_SIZE];
        const char*reply = "ACK: ";
        sockaddr_in client_addr{};
        socklen_t len = sizeof(client_addr);

        ssize_t r_bytes = recvfrom(sockfd,buffer, BUFFER_SIZE,
             0,(sockaddr*)&client_addr, &len);
        
        if(r_bytes < 0)
            throw SocketException("recvfrom() failed");
        
        buffer[r_bytes] = '\0';
        cout<<"Client: "<<buffer<<"\n";

        sendto(
            sockfd,
            reply,
            strlen(reply),
            0,
            (sockaddr*)&client_addr,
            len
        );
        cout<<"Ack Sent\n";
    }
public:
    void run()
    {
        while(true)
        {
            pid_t pid = fork();
            if (pid < 0)
                throw SocketException("fork() failed");
            if(pid == 0)
            {
                //child process
                handleCLient();
                _exit(0);
            }
            else
            {
                //parent process
                wait(nullptr);
            }
        }
    }
};


int main()
{
    try{
        UDPServer server;
        cout<<"UDP Fork Server running on port: " << PORT<<"\n";
        server.run();
    }
    catch(const SocketException &e)
    {
        cerr<<"Server Error: "<<e.what()<<"\n";
    }
    return 0;
}