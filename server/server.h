#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

class Server {
public:
    Server(uint16_t port);
    bool createSocket(int protocol = 0);
    bool bindListener();
    void listenPort();
    void closeConnection();

private:
    uint16_t port_;
    int socket_;
    int listener_;
    sockaddr_in addr_;
};

#endif // SERVER_H
