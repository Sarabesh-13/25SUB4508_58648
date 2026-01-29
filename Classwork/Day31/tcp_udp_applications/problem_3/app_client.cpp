// app_client.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctime>

class PatientDevice
{
    int sock;
    sockaddr_in server{};
    int patientId;

public:
    PatientDevice(int id) : patientId(id)
    {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        server.sin_family = AF_INET;
        server.sin_port = htons(9100);
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
    }

    void sendVitals()
    {
        while (true)
        {
            int hr = 60 + rand() % 60;
            int spo2 = 90 + rand() % 10;
            int bp = 80 + rand() % 40;
            time_t ts = time(nullptr);

            char buffer[256];
            snprintf(buffer, sizeof(buffer),
                     "%d,%ld,%d,%d,%d",
                     patientId, ts, hr, spo2, bp);

            sendto(sock, buffer, strlen(buffer), 0,
                   (sockaddr *)&server, sizeof(server));

            std::cout << "Vitals sent: " << buffer << std::endl;
            sleep(1);
        }
    }
};

int main()
{
    PatientDevice device(501);
    device.sendVitals();
    return 0;
}
