// app_server.cpp
#include <iostream>
#include <unordered_map>
#include <cstring>
#include <ctime>
#include <arpa/inet.h>
#include <unistd.h>

/*
 Project: Patient Vital Monitoring System

 Live vitals use UDP to minimize latency.
 Alerts are sent using TCP to guarantee delivery.
 Server maintains per-patient state and handles device failures
 using timeout-based cleanup.
*/

struct VitalData
{
    int heartRate;
    int spo2;
    int bp;
    time_t lastSeen;
};

class AlertManager
{
    int tcpSock;

public:
    AlertManager()
    {
        tcpSock = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9200);
        addr.sin_addr.s_addr = INADDR_ANY;

        bind(tcpSock, (sockaddr *)&addr, sizeof(addr));
        listen(tcpSock, 5);
    }

    void sendAlert(int patientId)
    {
        int client = accept(tcpSock, nullptr, nullptr);
        if (client >= 0)
        {
            char msg[128];
            snprintf(msg, sizeof(msg),
                     "ALERT: Patient %d abnormal vitals!", patientId);
            send(client, msg, strlen(msg), 0);
            close(client);
        }
    }
};

class VitalServer
{
    int udpSock;
    std::unordered_map<int, VitalData> patients;
    AlertManager alertManager;

public:
    VitalServer()
    {
        udpSock = socket(AF_INET, SOCK_DGRAM, 0);

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9100);
        addr.sin_addr.s_addr = INADDR_ANY;

        bind(udpSock, (sockaddr *)&addr, sizeof(addr));
    }

    void run()
    {
        char buffer[256];

        while (true)
        {
            sockaddr_in client{};
            socklen_t len = sizeof(client);

            int bytes = recvfrom(udpSock, buffer, sizeof(buffer) - 1, 0,
                                 (sockaddr *)&client, &len);
            buffer[bytes] = '\0';

            int pid, hr, spo2, bp;
            long ts;
            sscanf(buffer, "%d,%ld,%d,%d,%d", &pid, &ts, &hr, &spo2, &bp);

            patients[pid] = {hr, spo2, bp, time(nullptr)};

            if (hr > 120 || spo2 < 92)
            {
                alertManager.sendAlert(pid);
            }

            cleanupDisconnected();
            std::cout << "Updated vitals for patient " << pid << std::endl;
        }
    }

    void cleanupDisconnected()
    {
        for (auto it = patients.begin(); it != patients.end();)
        {
            if (time(nullptr) - it->second.lastSeen > 10)
            {
                std::cout << "Patient " << it->first << " disconnected\n";
                it = patients.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};

int main()
{
    VitalServer server;
    server.run();
    return 0;
}
