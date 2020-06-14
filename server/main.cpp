#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <thread>

#include "server.h"

int main()
{
    Server server(5555);

    if (!server.createSocket()) {
        std::cerr << "Error create socket" << std::endl;
        exit(1);
    }

    if (!server.bindListener()) {
        std::cerr << "Error bind listener" << std::endl;
        exit(1);
    }

    std::thread t(&Server::listenPort, server);
    t.detach();

    std::cin.get();
    return 0;
}
