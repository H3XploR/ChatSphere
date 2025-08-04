#pragma once
#include <string>
class client {
    public:
    std::string _hostName; //the real name of the host that the client is running on
    std::string _userName; //the username of the client on that host
    std::string _connectedTo; //and the server to which the client is connected
    std::string _reference; //any client can reference the channel using the name of the channel.
};