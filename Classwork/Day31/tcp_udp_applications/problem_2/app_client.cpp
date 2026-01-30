// app_client.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctime>

class VehicleClient {
    int sock;
    sockaddr_in server{};
    int vehicleId;

public:
    VehicleClient(int id) : vehicleId(id) {
        sock = socket(AF_INET, SOCK_DGRAM, 0);

        server.sin_family = AF_INET;
        server.sin_port = htons(9000);
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
    }

    void sendTelemetry() {
        while (true) {
            int speed = rand() % 120;
            int temp = 60 + rand() % 40;
            int rpm = 1000 + rand() % 3000;
            time_t ts = time(nullptr);

            char buffer[256];
            char timebuf[32];
            strftime(timebuf, sizeof(timebuf), "%Y-%m-%dT%H:%M:%S", localtime(&ts));

            snprintf(buffer, sizeof(buffer),
                     "%d,%s,%d,%d,%d",
                     vehicleId, timebuf, speed, temp, rpm);
            
            sendto(sock, buffer, strlen(buffer), 0,
                   (sockaddr*)&server, sizeof(server));

            std::cout << "Vehicle " << vehicleId
                      << " sent telemetry\n";
            sleep(1);
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./vehicle_client <vehicle_id>\n";
        return 1;
    }

    int vehicleId = std::stoi(argv[1]);
    VehicleClient client(vehicleId);
    client.sendTelemetry();

    return 0;
}
