#pragma once
#include <string>
#include <sys/socket.h>
#include <iostream>
#include <poll.h>
#include "client.hpp"
#include <vector>

class Server {
    public:
        int                 _fdSocket;
        std::vector<client> _channel;
        pollfd              _servPoll;

        void                createNewChannel(std::string channelName);

        Server();
        ~Server();
};