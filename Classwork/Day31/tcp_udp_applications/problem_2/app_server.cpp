// app_server.cpp
#include <iostream>
#include <unordered_map>
#include <deque>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

/*
 Project: Vehicle Diagnostic Telemetry System

 UDP is used because telemetry data is high-frequency and latency-sensitive.
 Occasional packet loss is acceptable, and UDP prevents slow clients
 from blocking the server.

 We use UDP instead of TCP because telemetry data is high-volume,
 continuous, and not all packets are critical.
 UDP avoids blocking, has low latency, and allows the server to
 keep receiving data even if some packets are lost.

*/

struct TelemetryData
{
    long timestamp;
    int speed;
    int temperature;
    int rpm;
};

class VehicleBuffer
{
    std::deque<TelemetryData> buffer;
    static const int LIMIT = 10;

public:
    void add(const TelemetryData &data, int vehicleId)
    {
        buffer.push_back(data);

        if (buffer.size() > LIMIT)
        {
            archive(buffer.front(), vehicleId);
            buffer.pop_front();
        }
    }

    void archive(const TelemetryData &data, int vehicleId)
    {
        std::ofstream file("vehicle_" + std::to_string(vehicleId) + ".log", std::ios::app);
        file << data.timestamp << "," << data.speed << ","
             << data.temperature << "," << data.rpm << "\n";
    }
};

class TelemetryServer
{
    int sock;
    std::unordered_map<int, VehicleBuffer> vehicles;

public:
    TelemetryServer()
    {
        sock = socket(AF_INET, SOCK_DGRAM, 0);

        sockaddr_in server{};
        server.sin_family = AF_INET;
        server.sin_port = htons(9000);
        server.sin_addr.s_addr = INADDR_ANY;

        bind(sock, (sockaddr *)&server, sizeof(server));
    }

    void run()
    {
        char buffer[256];

        while (true)
        {
            sockaddr_in client{};
            socklen_t len = sizeof(client);

            int bytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                 (sockaddr *)&client, &len);
            buffer[bytes] = '\0';

            int vid, speed, temp, rpm;
            long ts;
            sscanf(buffer, "%d,%ld,%d,%d,%d", &vid, &ts, &speed, &temp, &rpm);

            vehicles[vid].add({ts, speed, temp, rpm}, vid);
            std::cout << "Received data from Vehicle " << vid << std::endl;
        }
    }
};

int main()
{
    TelemetryServer server;
    server.run();
    return 0;
}
