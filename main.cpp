#include <iostream>
#include "command.hpp"
#include "server.hpp"

int main() {

    ServerHandler server;
    Command executor;
    std::string buf;

    if (!server.server_init()) {
        return 1;
    }

    if (!server.server_listen()) {
        return 2;
    }

    while (true) {
        std::cout << "Program started." << std::endl;
        server.close_listening_client();
        server.server_listen();

        if (server.server_accept_client()) {
            server.server_send_msg("/--------------------/\n");
            server.server_send_msg("menu\n");
            server.server_send_msg("Enter a command or type 'exit' to quit\n");

            while (true) {
                buf = server.server_read();
               

                if (buf == "exit\n") {
                    server.server_send_msg("Exiting the server...\n");
                    server.server_close();
                    std::cout << "Program finished." << std::endl;
                    return 0;
                }

                buf = executor.execute_command(buf);
               
                server.server_send_msg(buf);
                
            }
        }
    }

    return 0;
}
