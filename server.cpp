#include "server.hpp"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

ServerHandler::ServerHandler() : socket_fd(-1), client_socket_fd(-1) {}

ServerHandler::~ServerHandler() {
    if (socket_fd != -1) {
        close(socket_fd);
    }
    if (client_socket_fd != -1) {
        close(client_socket_fd);
    }
}

void ServerHandler::close_listening()
{
     close(socket_fd);
}

void ServerHandler::close_listening_client()
{
     close(client_socket_fd);
}

bool ServerHandler::server_init() {
    sockaddr_in add;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        std::cerr << "Cannot create a socket" << std::endl;
        return false;
    }
    add.sin_family = AF_INET;
    add.sin_port = htons(54000);
    inet_pton(AF_INET, "192.168.1.5", &add.sin_addr);
    if (bind(socket_fd, (sockaddr*)&add, sizeof(add)) < 0) {
        std::cerr << "Cannot bind" << std::endl;
        return false;
    }
    return true;
}

bool ServerHandler::server_listen() {
    if (listen(socket_fd, 2) < 0) {
        std::cerr << "Cannot listen" << std::endl;
        return false;
    }
    return true;
}

bool ServerHandler::server_accept_client() {
    sockaddr_in client;
    socklen_t client_size = sizeof(client);
    client_socket_fd = accept(socket_fd, (sockaddr*)&client, &client_size);
    if (client_socket_fd < 0) {
        std::cerr << "Problem with client connection" << std::endl;
        return false;
    }
    return true;
}


    void ServerHandler::server_send_msg(const std::string &message) 
{
    send(client_socket_fd, message.c_str(), message.size(), 0);
}

std::string ServerHandler::server_read() {
    ssize_t bytesRead = recv(client_socket_fd, static_cast<void*>(buffer.data()), buffer.size() - 1, 0);
    if (bytesRead < 0) 
    {
        return "Error for recv";
    } 
    
    else if (bytesRead == 0) 
    {
        return "Client closed the connection";
    }

    else {
        std::string buffer_str(buffer.data(), bytesRead);
        return buffer_str;
    }
}

void ServerHandler::server_close() {
    client_socket_fd = -1;
    if (client_socket_fd != -1) {
        close(client_socket_fd);
    }
    
}