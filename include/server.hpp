#pragma once
#include <string>
#include <sys/socket.h>
#include <iostream>
#include <poll.h>
#include "client.hpp"
#include "channel.hpp"
#include <vector>
#include <exception>
#include <unistd.h>
#include <netinet/in.h>

class client;
class channel;
class Server {
    public:
        int                 _fdSocket;
        int                 _port;
        std::vector<channel> _channel;
        pollfd              _servPoll;
        sockaddr_in         _serverAddress;
        void                createNewChannel(std::string channelName);

        Server();
        ~Server();
};