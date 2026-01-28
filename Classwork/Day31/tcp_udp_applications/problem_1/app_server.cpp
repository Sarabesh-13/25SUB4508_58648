//app_server.cpp
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

mutex db_mutex;
mutex log_mutex;

void logEvent(const string &level, const string &msg)
{
    lock_guard<mutex> lock(log_mutex);
    ofstream log(LOG_FILE, ios::app);
    log << "[" << level << "] " << msg << endl;
}

unordered_map<string, double> loadAccounts()
{
    lock_guard<mutex> lock(db_mutex);
    unordered_map<string, double> accounts;

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
    return accounts;
}

void handleClient(int client_fd)
{
    static unordered_map<string, double> accounts = loadAccounts();

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

    if (cmd != "VERIFY")
    {
        logEvent("CRITICAL", "Invalid request");
        write(client_fd, "INVALID\n", 8);
    }
    else if (accounts.count(acc))
    {
        string response = "VALID " + to_string(accounts[acc]) + "\n";
        write(client_fd, response.c_str(), response.size());
        logEvent("INFO", "Verified account " + acc);
    }
    else
    {
        write(client_fd, "INVALID\n", 8);
        logEvent("CRITICAL", "Invalid account " + acc);
    }

    close(client_fd);
}

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

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
        thread(handleClient, client_fd).detach();
    }
}

/*
This program simulates a centralized account verification bank server using TCP sockets in C++.
It listens for client connections, verifies account numbers against a local database, and responds with account validity and balance.
It also logs events to a log file with appropriate severity levels.

we prefer TCP/IP over UDP here because TCP provides reliable, ordered, and error-checked delivery of data, which is crucial for financial transactions and account verification processes.
*/