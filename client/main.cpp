#include <iostream>
#include <string>

#include "client.h"

int main()
{
    Client client(5555);

    if (!client.createSocket()) {
        std::cerr << "Error open socked" << std::endl;
        exit(1);
    }

    if (!client.connectToServer()) {
        std::cerr << "Error connect socked" << std::endl;
        exit(1);
    }

    const std::string message = "Hello there!";

    client.sendMessage(message);
    client.closeConnection();
    return 0;
}
