//
// Created by Malik Zharykov on 06.12.2023.
//

#include "glcraft.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread>
#include <iostream>

void server_thread(Network* net) {
    struct sockaddr_in servaddr;

    if ( (net->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(net->port);

    if ( bind(net->sockfd, (const struct sockaddr *)&servaddr,
              sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in cliaddr;
    char buffer[sizeof(Datagram)];

    memset(&cliaddr, 0, sizeof(cliaddr));
    socklen_t len = sizeof(cliaddr);  //len is value/result

    size_t offset = 0;

    while (int n = recvfrom(net->sockfd, ((char *)buffer) + offset, sizeof(Datagram) - offset,
                     MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                     &len)) {
        offset += n;
        offset %= sizeof(Datagram);

        if (offset != 0) {
            continue;
        }

        // Save position from client
        const Datagram* d = (const Datagram*)buffer;

        player->mutex.lock();
        player->position.x = d->x;
        player->position.y = d->y;
        player->position.z = d->z;
        player->look.x = d->rx;
        player->look.y = d->ry;
        player->mutex.unlock();

        //std::cout << "from client: " << d->x << ", " <<  d->y << ", " <<  d->z << ", " << std::endl;

        // Send current position to client
        Datagram my;
        my.x = camera->position.x;
        my.y = camera->position.y;
        my.z = camera->position.z;
        my.rx = camera->look.x;
        my.ry = camera->look.y;

        sendto(net->sockfd, (const char *)&my, sizeof(my),
               0, (const struct sockaddr *) &cliaddr,
               len);
    }
}

void client_thread(Network* net) {
    char buffer[sizeof(Datagram)];
    struct sockaddr_in servaddr;

    if ( (net->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(net->port);
    servaddr.sin_addr.s_addr = inet_addr(net->host);

    while (true) {
        Datagram my;

        my.x = camera->position.x;
        my.y = camera->position.y;
        my.z = camera->position.z;
        my.rx = camera->look.x;
        my.ry = camera->look.y;

        sendto(net->sockfd, (const char *)&my, sizeof(Datagram),
               0, (const struct sockaddr *) &servaddr,
               sizeof(servaddr));


        size_t offset = 0;
        socklen_t len;
        while (int n = recvfrom(net->sockfd, ((char *)buffer) + offset, sizeof(Datagram) - offset,
                                MSG_WAITALL, (struct sockaddr *) &servaddr,
                                &len)) {
            offset += n;
            offset %= sizeof(Datagram);

            if (offset != 0) {
                continue;
            }

            // Save position from client
            const Datagram* d = (const Datagram*)buffer;

            player->mutex.lock();
            player->position.x = d->x;
            player->position.y = d->y;
            player->position.z = d->z;
            player->look.x = d->rx;
            player->look.y = d->ry;
            player->mutex.unlock();

            //std::cout << "from server: " << d->x << ", " <<  d->y << ", " <<  d->z << ", " << std::endl;
            break;
        }
    }
}

void Network::start_server(uint16_t port) {
    this->port = port;
    sthread = new std::thread(server_thread, this);
}


void Network::start_client(const char* host, uint16_t port) {
    this->port = port;
    this->host = host;
    cthread = new std::thread(client_thread, this);
}