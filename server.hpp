#ifndef SERVER_HPP
#define SERVER_HPP

#include <array>
#include <string>

class ServerHandler {
public:
    ServerHandler();
    ~ServerHandler();

    bool server_init();
    bool server_listen();
    bool server_accept_client();
    void server_send_msg(const std::string& message);
    void close_listening();
    void close_listening_client();

    std::string server_read();
    void server_close();

private:
    int socket_fd;
    int client_socket_fd;
    std::array<char, 256> buffer;
};

#endif
