#include "../include/client.hpp"
client::client(std::string username) : _hostName(getHostName()), _userName(username) {
    std::cout << "client created\n";
}

client::~client() {
    std::cout << "client destroyed\n";
}

std::string client::getHostName() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        return std::string(hostname);
    } else {
        return "";
    }
}

std::ostream& operator<<(std::ostream& os, client Client) {
  os << "hostname: " << Client._hostName << std::endl;
  os << "username: " << Client._userName << std::endl;
  return os;
}