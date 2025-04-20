#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <winsock2.h>
#include <string>

class ClientHandler
{
private:
    SOCKET clientSocket;
    std::string clientIp;
    int clientPort;

    void handleClient();
    std::string readFile(const std::string& fileName);
    std::string composeHTTPResponse(const std::string& status, const std::string& body);
    void sendResponse(const std::string& status, const std::string& body);

public:
    explicit ClientHandler(SOCKET socket, std::string clientIp, int clientPort);
    void operator()();
};


#endif //CLIENT_HANDLER_H
