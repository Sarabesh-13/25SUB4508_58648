#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090
#define BUFFER 1024
#define ACCOUNT_DB "accounts.db"
#define LOG_FILE "bank.log"

using namespace std;


void error(const char * str)
{
    perror(str);
    exit(0);
}

mutex db_mutex;
mutex log_mutex;

class ServerSocket {
    int server_fd;

public:
    ServerSocket() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) { error("socket connection failed"); }
    }

    void bindAndListen() {
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(PORT);

        if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0)
            error("Bind failed");

        if (listen(server_fd, 5) < 0)
            error("Listen failed");
    }

    int acceptClient() {
        sockaddr_in client_address{};
        socklen_t len = sizeof(client_address);
        return accept(server_fd, (sockaddr*)&client_address,&len);
    }

    ~ServerSocket() { close(server_fd); }
};



class Logger {
public:
    static void log(const string& level, const string& msg) {
        lock_guard<mutex> lock(log_mutex);
        ofstream out(LOG_FILE, ios::app);
        out << "[" << level << "] " << msg << endl;
    }
};



class Account {
public:
    string accountNo;
    double balance;

    Account() = default;
    Account(string a, double b) : accountNo(a), balance(b) {}
};



class AccountRepository {
public:
    static vector<Account> load() {
        lock_guard<mutex> lock(db_mutex);
        vector<Account> accounts;

        ifstream in(ACCOUNT_DB);
        if (!in) {
            ofstream out(ACCOUNT_DB);
            out << "1001,5000\n1002,3000\n";
            out.close();
            in.open(ACCOUNT_DB);
        }

        string line;
        while (getline(in, line)) {
            string acc, bal;
            stringstream ss(line);
            getline(ss, acc, ',');
            getline(ss, bal);
            accounts.emplace_back(acc, stod(bal));
        }
        return accounts;
    }

    static void save(const vector<Account>& accs) {
        lock_guard<mutex> lock(db_mutex);
        ofstream out(ACCOUNT_DB);
        for (auto& a : accs)
            out << a.accountNo << "," << a.balance << endl;
    }
};



class Bank {
    vector<Account> accounts;

    Bank() {
        accounts = AccountRepository::load();
    }

public:
    static Bank& instance() {
        static Bank bank;
        return bank;
    }

    Account* findAccount(const string& acc) {
        for (auto& a : accounts)
            if (a.accountNo == acc) return &a;
        return nullptr;
    }

    string balance(const string& acc) {
        auto* a = findAccount(acc);
        if (!a) {
            Logger::log("CRITICAL", "Invalid account " + acc);
            return "Invalid account\n";
        }
        Logger::log("INFO", "Balance enquiry " + acc);
        return "Balance: " + to_string(a->balance) + "\n";
    }

    string withdraw(const string& acc, double amt) {
        auto* a = findAccount(acc);
        if (!a) {
            Logger::log("CRITICAL", "Invalid account " + acc);
            return "Invalid account\n";
        }
        if (a->balance < amt) {
            Logger::log("CRITICAL", "Insufficient funds " + acc);
            return "Insufficient funds\n";
        }
        a->balance -= amt;
        AccountRepository::save(accounts);
        Logger::log("CRITICAL", "Withdraw " + acc);
        return "Withdraw successful\n";
    }
};



class ATMService {
public:
    static string process(const string& req) {
        string cmd, acc;
        double amt;
        stringstream ss(req);
        ss >> cmd >> acc;

        if (cmd == "BALANCE")
            return Bank::instance().balance(acc);

        if (cmd == "WITHDRAW") {
            ss >> amt;
            return Bank::instance().withdraw(acc, amt);
        }

        return "Invalid command\n";
    }
};



void handleClient(int fd) {
    char buf[BUFFER]{};
    int n = read(fd, buf, BUFFER - 1);
    if (n <= 0) {
        close(fd);
        return;
    }

    buf[n] = '\0';
    string response = ATMService::process(buf);
    write(fd, response.c_str(), response.size());
    close(fd);
}


int main() {
    ServerSocket server;
    server.bindAndListen();

    cout << "ATM Server running on port " << PORT << endl;

    while (true) {
        int fd = server.acceptClient();
        thread(handleClient, fd).detach();
    }
}
