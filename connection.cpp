#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "connection.h"

void connection::connect(int port, std::string host)
{   
    socketId = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&client, 0 , sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(host.c_str());
    client.sin_port = htons(port);
    bind(socketId, (struct sockaddr*)&client, sizeof(client));
}

int connection::receive(void * buffer, size_t bufferSize)
{
    int received;
    socklen_t length = sizeof(client);
    received = recvfrom(socketId, buffer, bufferSize, 0 , (struct sockaddr*)&client, &length);
    return received;
}