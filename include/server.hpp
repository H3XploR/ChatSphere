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
#include <sys/epoll.h>
#define EPOLL_QUEUE_LEN  10
#define MAX_EPOLL_EVENTS_PER_RUN 10
#define EPOLL_RUN_TIMEOUT 1000 // 1000 ms (1 second) is a common default
class client;
class channel;
class Server {
    public:
        int                       _fdSocket;
        int                       _port;
        std::vector<channel>      _channel;
        pollfd                    _servPoll;
        sockaddr_in               _serverAddress;
        int                       _epfd;
    struct epoll_event _ev[MAX_EPOLL_EVENTS_PER_RUN];
        int                       _client_sock;
        void                createNewChannel(std::string channelName);

        Server();
        ~Server();
};