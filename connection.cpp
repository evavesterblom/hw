#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include "connection.h"
#include <errno.h>

void connection::connect(int port, std::string host){   
    socketId = socket(AF_INET, SOCK_DGRAM, 0);
    std::cout << "Connection: socket " << socketId << "\n";
    memset(&client, 0 , sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(host.c_str());
    client.sin_port = htons(port);
    if (-1 == bind(socketId, (struct sockaddr*)&client, sizeof(client)))
    {
        int err = errno;
        std::cout << "Connection: bind failed " << err << "\n";
    }
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    int opt = setsockopt(socketId, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    std::cout << "Connection opening: option" << opt << "\n";

}

int connection::receive(void * buffer, size_t bufferSize){
    int received;
    socklen_t length = sizeof(client);
    received = recvfrom(socketId, buffer, bufferSize, 0 , (struct sockaddr*)&client, &length);
    return received;
}

connection::~connection(){
    std::cout << "Connection opening: closing socket (destr)" << "\n";
    close(socketId);
}

void connection::closed(){
    std::cout << "Connection opening: closing socket" << "\n";
    close(socketId);
}