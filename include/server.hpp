#pragma once
#include <string>
#include <sys/socket.h>
#include <iostream>
#include <poll.h>
#include "client.hpp"
#include "channel.hpp"
#include <vector>

class client;
class channel;
class Server {
    public:
        int                 _fdSocket;
        std::vector<channel> _channel;
        pollfd              _servPoll;

        void                createNewChannel(std::string channelName);

        Server();
        ~Server();
};