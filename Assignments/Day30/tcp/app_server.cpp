#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9090
#define BUFFER 1024
#define DB_FILE "employees.db"

using namespace std;

mutex db_mutex;

class ServerSocket {
    int server_fd;

public:
    ServerSocket() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) { perror("socket"); exit(1); }
    }

    void bindAndListen() {
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(PORT);

        if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
            perror("bind"); exit(1);
        }
        if (listen(server_fd, 5) < 0) {
            perror("listen"); exit(1);
        }
    }

    int acceptClient() {
        return accept(server_fd, nullptr, nullptr);
    }

    ~ServerSocket() { close(server_fd); }
};

class Employee
{
    string username, password, address, phone, designation, role;
    double salary;

public:
    Employee(string u, string pw, string a, string p,
             string d, double s, string r)
        : username(u), password(pw), address(a),
          phone(p), designation(d), salary(s), role(r) {}

    Employee(string u, string pw)
        : username(u), password(pw), address(""), phone(""), designation(""), salary(0), role("admin") {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }

    void updateAddress(const string &a) { address = a; }
    void updatePhone(const string &p) { phone = p; }
    void updateDesignation(const string &d) { designation = d; }

    string serialize() const
    {
        stringstream ss;
        ss << username << "," << password << ","
           << address << "," << phone << ","
           << designation << "," << salary << "," << role;
        return ss.str();
    }

    string toString() const {
        stringstream ss;
        ss << "\nUsername: " << username
           << "\nAddress: " << (address.empty() ? "N/A" : address)
           << "\nPhone: " << (phone.empty() ? "N/A" : phone)
           << "\nDesignation: " << (designation.empty() ? "N/A" : designation)
           << "\nSalary: " << salary << "\n";
        return ss.str();
    }
};

vector<Employee> loadEmployees() {
    lock_guard<mutex> lock(db_mutex);
    vector<Employee> emps;
    ifstream file(DB_FILE);

    if (!file.is_open()) {
        ofstream out(DB_FILE);
        out << "admin,admin123,,,,100000,admin\n";
        out << "john,john123,Street1,1111111111,Manager,50000,user\n";
        out << "jane,jane123,Street2,2222222222,Engineer,40000,user\n";
        out.close();
        file.open(DB_FILE);
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;   

        stringstream ss(line);
        string u, pw, a, ph, d, sal, r;

        if (!getline(ss, u, ',')) continue;
        if (!getline(ss, pw, ',')) continue;
        if (!getline(ss, a, ',')) continue;
        if (!getline(ss, ph, ',')) continue;
        if (!getline(ss, d, ',')) continue;
        if (!getline(ss, sal, ',')) continue;
        if (!getline(ss, r)) continue;

        if (sal.empty()) continue;    

        double s;
        try {
            s = stod(sal);
        } catch (...) {
            continue;                 
        }

        emps.emplace_back(u, pw, a, ph, d, s, r);
    }
    return emps;
}


void saveEmployees(const vector<Employee>& emps) {
    lock_guard<mutex> lock(db_mutex);
    ofstream out(DB_FILE);
    for (auto& e : emps) {
        out << e.serialize() << "\n";
    }
}

//socket_helpers

void sendMsg(int fd, const string& msg) {
    write(fd, msg.c_str(), msg.size());
}

string recvMsg(int fd) {
    char buf[BUFFER]{};
    int n = read(fd, buf, BUFFER - 1);
    if (n <= 0) return "";
    buf[n] = '\0';
    string s(buf);
    s.erase(remove(s.begin(), s.end(), '\n'), s.end());
    return s;
}

void adminMenu(int fd, vector<Employee>& emps) {
    while (true) {
        sendMsg(fd,
            "\n--- ADMIN MENU ---\n"
            "1. View Employees (Sorted)\n"
            "2. Add Employee\n"
            "3. Logout\nChoice: ");

        string ch = recvMsg(fd);

        if (ch == "1") {
            sort(emps.begin(), emps.end(),
                 [](auto& a, auto& b) {
                     return a.getUsername() < b.getUsername();
                 });
            for (auto& e : emps)
                sendMsg(fd, e.toString());
        }
        else if (ch == "2") {
            string u,pw,a,ph,d,sal;
            sendMsg(fd,"Username: "); u=recvMsg(fd);
            sendMsg(fd,"Password: "); pw=recvMsg(fd);
            sendMsg(fd,"Address: "); a=recvMsg(fd);
            sendMsg(fd,"Phone: "); ph=recvMsg(fd);
            sendMsg(fd,"Designation: "); d=recvMsg(fd);
            sendMsg(fd,"Salary: "); sal=recvMsg(fd);

            emps.emplace_back(u,pw,a,ph,d,stod(sal),"user");
            saveEmployees(emps);
        }
        else if (ch == "3") break;
    }
}

void userMenu(int fd, Employee& emp, vector<Employee>& emps) {
    while (true) {
        sendMsg(fd,
            "\n--- USER MENU ---\n"
            "1. View Profile\n"
            "2. Update Address\n"
            "3. Update Phone\n"
            "4. Update Designation\n"
            "5. Logout\nChoice: ");

        string ch = recvMsg(fd);

        if (ch == "1") sendMsg(fd, emp.toString());
        else if (ch == "2") { sendMsg(fd,"New Address: "); emp.updateAddress(recvMsg(fd)); }
        else if (ch == "3") { sendMsg(fd,"New Phone: "); emp.updatePhone(recvMsg(fd)); }
        else if (ch == "4") { sendMsg(fd,"New Designation: "); emp.updateDesignation(recvMsg(fd)); }
        else if (ch == "5") break;

        saveEmployees(emps);
    }
}

void handleClient(int fd) {
    sendMsg(fd,"Username: ");
    string user = recvMsg(fd);
    sendMsg(fd,"Password: ");
    string pass = recvMsg(fd);

    auto emps = loadEmployees();
    auto it = find_if(emps.begin(), emps.end(),
        [&](const Employee& e) {
            return e.getUsername() == user &&
                   e.getPassword() == pass;
        });

    if (it == emps.end()) {
        sendMsg(fd,"\nInvalid username or password\n");
        close(fd);
        return;
    }
    cerr << "ROLE=[" << it->getRole() << "] size=" << it->getRole().size() << "\n";
    if (it->getRole() == "admin") {
        adminMenu(fd, emps);
    } else {
        userMenu(fd, *it, emps);
    }

    close(fd);
}


int main() {
    ServerSocket server;
    server.bindAndListen();

    cout << "Server running on port " << PORT << endl;

    while (true) {
        int fd = server.acceptClient();
        thread(handleClient, fd).detach();
    }
}
