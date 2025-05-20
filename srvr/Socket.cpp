#include "Socket.h"

#include <iostream>
#include <string>

#define SERVER_IP "192.168.108.128"
#define BUFFER_LENGTH 4048
#define PORT 51051

MySocket::MySocket() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
    }
}

MySocket::~MySocket() {
    WSACleanup();
}

SOCKET MySocket::openClientConnection() {
    sockaddr_in serverAddress{};

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        return INVALID_SOCKET;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Connection to server failed!" << std::endl;
        closesocket(clientSocket);
        return INVALID_SOCKET;
    }

    return clientSocket;
}

SOCKET MySocket::openServerConnection() {
    sockaddr_in serverAddress{}, clientAddress{};

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        return INVALID_SOCKET;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Binding socket failed!" << std::endl;
        closesocket(serverSocket);
        return INVALID_SOCKET;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed!" << std::endl;
        closesocket(serverSocket);
        return INVALID_SOCKET;
    }

    std::cout << "Server is listening for connections..." << std::endl;

    int clientSize = sizeof(clientAddress);
    SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed!" << std::endl;
        closesocket(serverSocket);
        return INVALID_SOCKET;
    }

    closesocket(serverSocket);  // Optionally close the server socket if you only expect one connection
    return clientSocket;
}

void MySocket::sendMessage(SOCKET connection, const std::string& str) {
    int bytesSent = send(connection, str.c_str(), static_cast<int>(str.size()), 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Failed to send message!" << std::endl;
    }
}

std::string MySocket::receiveMessage(SOCKET connection) {
    char buffer[BUFFER_LENGTH]{};
    int bytesReceived = recv(connection, buffer, BUFFER_LENGTH - 1, 0);
    if (bytesReceived <= 0) {
        std::cerr << "Failed to receive message or connection closed!" << std::endl;
        return "";
    }
    return std::string(buffer, bytesReceived);
}

void MySocket::closeConnection(SOCKET socket_descriptor) {
    closesocket(socket_descriptor);
}
