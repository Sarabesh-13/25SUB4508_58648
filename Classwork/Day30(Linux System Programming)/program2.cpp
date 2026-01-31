// program to implement UDP Fork Client
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

class UDPClient
{
private:
    int sockfd;
    sockaddr_in server_addr;
public:
    explicit UDPClient(const string &ip): sockfd(-1)
    {
        createSocket();
        setupServer(ip);
    }
    ~UDPClient(){
        if(sockfd != -1)
            close(sockfd); 
    }
private:
    void createSocket(){
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd < 0)
            throw SocketException("Socket Creation Failed");
    }

    void setupServer(const string &ip)
    {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        if(inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) == 0)
            throw SocketException("Invalid Server IP address");
    }

public:
    void sendMessage(const string &message)
    {
        char buffer[BUFFER_SIZE];
        socklen_t len = sizeof(server_addr);
        sendto(
            sockfd,
            message.c_str(),
            message.length(),
            0,
            (sockaddr *)&server_addr,
            len
        );

        recvfrom(
            sockfd,
            buffer,
            BUFFER_SIZE,
            0,
            nullptr,
            nullptr
        );

        cout<<"Server: "<<buffer<<"\n";
        
    }


};


int main()
{
    try{
        UDPClient client("127.0.0.1");

        string msg;
        while(true)
        {
            cout<<"\nClient: ";
            getline(cin, msg);
            if(msg == "exit"){
                break;
            }
            client.sendMessage(msg);
        }
    }
    catch(const SocketException &e)
    {
        cerr<<"Client Error: "<<e.what()<<"\n";
    }

    return 0;
}