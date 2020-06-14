#include "server.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <iostream>

Server::Server(uint16_t port)
    : port_(port)
{
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = htonl(INADDR_ANY);
}

bool Server::createSocket(int protocol)
{
    listener_ = socket(AF_INET, SOCK_STREAM, protocol);
    return (listener_ != -1);
}

bool Server::bindListener()
{
    if(bind(listener_, reinterpret_cast<sockaddr *>(&addr_), sizeof(addr_)) < 0) {
        return false;
    }
    return true;
}

void Server::listenPort()
{
    listen(listener_, 1);

    while(true) {
        socket_ = accept(listener_, nullptr, nullptr);
        if(socket_ >= 0) {
            char buf[1024];
            while(true) {
                if(recv(socket_, buf, 1024, 0) <= 0) {
                    break;
                }
                std::cout << buf << std::endl;
                std::string answer = "I got your message.";
                send(socket_, answer.c_str(), answer.size(), 0);
            }
        }
        closeConnection();
    }
}

void Server::closeConnection()
{
    close(socket_);
}
