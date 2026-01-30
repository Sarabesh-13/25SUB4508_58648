#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace std;

#define PORT 9090
#define BUFFER 1024
#define DB_FILE "accounts.txt"
#define LOG_FILE "server.log"

class VerificationServer
{
private:
    int server_fd;
    unordered_map<string, double> accounts;
    mutex db_mutex;
    mutex log_mutex;

    void loadAccounts()
    {
        lock_guard<mutex> lock(db_mutex);
        ifstream in(DB_FILE);

        if (!in)
        {
            ofstream out(DB_FILE);
            out << "1001,5000\n1002,3000\n";
            out.close();
            in.open(DB_FILE);
        }

        string line, acc, bal;
        while (getline(in, line))
        {
            stringstream ss(line);
            getline(ss, acc, ',');
            getline(ss, bal);
            accounts[acc] = stod(bal);
        }
    }

    void logEvent(const string &level, const string &msg)
    {
        lock_guard<mutex> lock(log_mutex);
        ofstream log(LOG_FILE, ios::app);
        log << "[" << level << "] " << msg << endl;
    }

    void handleClient(int client_fd)
    {
        char buf[BUFFER]{};
        int n = read(client_fd, buf, BUFFER - 1);

        if (n <= 0)
        {
            close(client_fd);
            return;
        }

        string cmd, acc;
        stringstream ss(buf);
        ss >> cmd >> acc;

        if (cmd == "VERIFY" && accounts.count(acc))
        {
            string resp = "VALID " + to_string(accounts[acc]) + "\n";
            write(client_fd, resp.c_str(), resp.size());
            logEvent("INFO", "Verified account " + acc);
        }
        else
        {
            write(client_fd, "INVALID\n", 8);
            logEvent("CRITICAL", "Invalid account attempt");
        }

        close(client_fd);
    }

public:
    VerificationServer()
    {
        loadAccounts();
    }

    void start()
    {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(PORT);

        bind(server_fd, (sockaddr *)&addr, sizeof(addr));
        listen(server_fd, 10);

        cout << "Verification Server running on port " << PORT << endl;

        while (true)
        {
            int client_fd = accept(server_fd, nullptr, nullptr);
            thread(&VerificationServer::handleClient, this, client_fd).detach();
        }
    }
};

int main()
{
    VerificationServer server;
    server.start();
    return 0;
}