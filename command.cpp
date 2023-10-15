#include "command.hpp"
#include <cstdlib>
#include <iostream>
#include <algorithm>

Command::Command() : commands{
    {"calculator", "gnome-calculator"},
    {"terminal", "gnome-terminal"},
    {"firefox", "firefox"},
    {"date", "date"},
    {"battery", "upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep 'percentage'"},
    {"shutdown", "shutdown now"}
} {}

std::string Command::execute_command(const std::string& cmd) {
    std::string cleaned_cmd = cmd;

    // Use popen to capture output and error messages
    std::string result;
    FILE* fp = popen(cleaned_cmd.c_str(), "r");
    if (fp) {
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
            result += buffer;
        }
        int status = pclose(fp);
        if (status == 0) {
            return result;
        } else {
            return "Command execution failed";
        }
    } else {
        return "Failed to execute command";
    }
}
