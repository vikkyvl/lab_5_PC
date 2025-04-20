#include "client_handler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#define ROOT_FOLDER "pages"
#define BUFFER_SIZE 4096

ClientHandler::ClientHandler(SOCKET socket, std::string clientIp, int clientPort) : clientSocket(socket), clientIp(std::move(clientIp)), clientPort(clientPort) {}

void ClientHandler::operator()()
{
    handleClient();
    closesocket(clientSocket);
}

void ClientHandler::handleClient()
{
    char buffer[BUFFER_SIZE];
    std::string status, body, method, path, version;

    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived <= 0)
    {
        closesocket(clientSocket);
        return;
    }

    buffer[bytesReceived] = 0;
    std::string request(buffer);
    std::istringstream iss(request);

    iss >> method >> path >> version;

    //std::cout << "Client connected from IP: " << clientIp << " | Port: " << clientPort << std::endl;
    //std::cout << "Request: " << method << " " << path << " " << version << std::endl;

    if(method != "GET")
    {
        status = "405 Method Not Allowed";
        body = "<h1>405 Method Not Allowed</h1>";
        sendResponse(status, body);
        //std::cout << "Response status: " << status << std::endl;
        closesocket(clientSocket);
        return;
    }

    if(path == "/")
    {
        path = "/index.html";
    }

    std::string content = readFile(path);

    if(!content.empty())
    {
        status = "200 OK";
        body = content;
    }
    else
    {
        status = "404 Not Found";
        body = "<h1>404 Not Found</h1>";
    }

    sendResponse(status, body);
    //std::cout << "Response status: " << status << std::endl;
}

std::string ClientHandler::readFile(const std::string& fileName)
{
    std::ifstream file(std::string(ROOT_FOLDER) + fileName);
    if (!file.is_open()) return "";
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::string ClientHandler::composeHTTPResponse(const std::string& status, const std::string& body)
{
    std::ostringstream response;
    response << "HTTP/1.1 " << status << "\r\n"
             << "Content-Type: text/html\r\n"
             << "Content-Length: " << body.size() << "\r\n"
             //<< "Connection: close\r\n"
             << "\r\n"
             << body;
    return response.str();
}

void ClientHandler::sendResponse(const std::string& status, const std::string& body)
{
    std::string response = composeHTTPResponse(status, body);
    send(clientSocket, response.c_str(), response.size(), 0);
}
