//
// Created by Malik Zharykov on 06.12.2023.
//

#ifndef GLCRAFT_NETWORK_HPP
#define GLCRAFT_NETWORK_HPP

#include <thread>

#define MAGIC_NUM = 0xBC

#pragma pack(push, 1)
struct Datagram {
    uint8_t magic;
    float x;
    float y;
    float z;
    float rx;
    float ry;
};
#pragma pack(pop)

class Network {
public:
    int sockfd = -2;
    uint16_t port = 0;
    const char* host = "";
    std::thread* sthread;
    std::thread* cthread;

    void start_server(uint16_t port);
    void start_client(const char* host, uint16_t port);
};


#endif //GLCRAFT_NETWORK_HPP
