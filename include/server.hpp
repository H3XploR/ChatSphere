#pragma once
#include <stdint.h>
#include <string>
#include <list>
#include <sys/socket.h>
#include <iostream>
#include <poll.h>
#include "client.hpp"
#include "channel.hpp"
#include "parser.hpp"
#include <vector>
#include <exception>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <arpa/inet.h> // pour inet_ntoa
#define EPOLL_QUEUE_LEN  10
#define MAX_EPOLL_EVENTS_PER_RUN 10
#define EPOLL_RUN_TIMEOUT 1000 // 1000 ms (1 second) is a common default
class client;
class channel;
class parser;
class Server {
    public:
        int                                     _fdSocket;
        int                                     _port;
        std::string                             _password;
        std::vector<channel>                    _channel;
        std::list<std::pair<int, client> >      _client;
        pollfd                                  _servPoll;
        sockaddr_in                             _serverAddress;
        int                                     _epfd;
        struct epoll_event                      _ev[MAX_EPOLL_EVENTS_PER_RUN];
        int                                     _client_sock;
        void                createNewChannel(std::string channelName);
        void                handle_io_on_socket(int fd);
        void                handle_command(parser& parsed_command, client& leclient, int fd);
        int                 isInChannel();
        void                send_to_fd(std::string message, int fd);
        Server(std::string password);
        ~Server();
            // Prototypes des handlers de commandes IRC
        void handle_pass(const parser& cmd, client& leclient, int fd);
        void handle_nick(const parser& cmd, client& leclient, int fd);
        void handle_user(const parser& cmd, client& leclient, int fd);
        void handle_join(const parser& cmd, client& leclient, int fd);
        void handle_privmsg(const parser& cmd, client& leclient, int fd);
        void handle_part(const parser& cmd, client& leclient, int fd);
        void handle_quit(const parser& cmd, client& leclient, int fd);
        void handle_kick(const parser& cmd, client& leclient, int fd);
        void handle_invite(const parser& cmd, client& leclient, int fd);
        void handle_topic(const parser& cmd, client& leclient, int fd);
        void handle_mode(const parser& cmd, client& leclient, int fd);
        void handle_names(const parser& cmd, client& leclient, int fd);
};

std::ostream& operator<<(std::ostream& os, const Server& server);
uint32_t ipToDecimal(const sockaddr_in& addr);