#ifndef CLIENT_DATA_H
#define CLIENT_DATA_H


#include <string>
#include <winsock2.h>

struct ClientData
{
    SOCKET socket;
    std::string ip;
    int port;
};


#endif //CLIENT_DATA_H
