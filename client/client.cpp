#include "client.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Client::Client(uint16_t port)
    :port_(port)
{
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(port_);
    server_addr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

bool Client::createSocket(int protocol)
{
    socket_ = socket(AF_INET, SOCK_STREAM, protocol);
    return (socket_ != -1);
}

bool Client::connectToServer()
{
    return (connect(socket_, reinterpret_cast<sockaddr *>(&server_addr_), sizeof(server_addr_)) != -1);
}

void Client::sendMessage(std::string message)
{
    send(socket_, message.c_str(), message.size(), 0);

    // Receive answer from server
    char buffer[1024];
    recv(socket_, buffer, 1024, 0);
    printf(buffer);
}

void Client::closeConnection()
{
    close(socket_);
}
