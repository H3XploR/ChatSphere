#include "../include/server.hpp"

int main(void) {
    try {
        Server irc(std::string("password"));
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}