#include "../include/server.hpp"
#include <iostream>
#include <exception>
#include <unistd.h>

Server::Server()
                :_fdSocket(socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0)) {
    std::cout << "server loading....\n";
    std::cout << "fd_socket: " << _fdSocket << "\n";
    if (_fdSocket < 0)
        throw std::runtime_error("socket creation failed");
}

Server::~Server() {
    if (_fdSocket >= 0) {
        close(_fdSocket);
        std::cout << "Socket " << _fdSocket << " closed.\n";
    }
}

/*
   To create a new channel or become part of an existing channel, a user
   is required to JOIN the channel.  If the channel doesn't exist prior
   to joining, the channel is created and the creating user becomes a
   channel operator.  If the channel already exists, whether or not your
   request to JOIN that channel is honoured depends on the current modes
   of the channel. For example, if the channel is invite-only, (+i),
   then you may only join if invited.  As part of the protocol, a user
   may be a part of several channels at once, but a limit of ten (10)
   channels is recommended as being ample for both experienced and
   novice users.  See section 8.13 for more information on this.
*/
void Server::createNewChannel(std::string channelName) {
    // Implementation for creating a new channel
    // This function should handle the logic of creating a new channel
    // and adding it to the server's list of channels.
    std::cout << "Creating a new channel " << channelName << "...\n";
    // Logic to create a new channel goes here

}