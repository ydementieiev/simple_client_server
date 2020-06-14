#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
#include <string>

class Client {
public:
    Client(uint16_t port);

    bool createSocket(int protocol = 0);
    bool connectToServer();
    void sendMessage(std::string message);
    void closeConnection();

private:
    uint16_t port_;
    int socket_;
    sockaddr_in server_addr_;
};

#endif // CLIENT_H
