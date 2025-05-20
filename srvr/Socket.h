#pragma once

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include <string>

class MySocket {
public:
    MySocket();
    ~MySocket();

    SOCKET openServerConnection();
    SOCKET openClientConnection();

    void sendMessage(SOCKET connection, const std::string& str);
    std::string receiveMessage(SOCKET connection);

    void closeConnection(SOCKET socket_descriptor);
};
