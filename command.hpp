#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <map>

class Command {
public:
    Command();

    std::string execute_command(const std::string& cmd);

private:
    std::map<std::string, std::string> commands;
};

#endif
