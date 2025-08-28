#include "../include/server.hpp"


Server::Server() : _fdSocket(socket(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0)), _port(8080) {
    std::cout << "server loading....\n";
    std::cout << "fd_socket: " << _fdSocket << "\n";
    if (_fdSocket < 0)
        throw std::runtime_error("socket creation failed");
      // specifying address
    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_port = htons(_port);
    _serverAddress.sin_addr.s_addr = INADDR_ANY;
    // sending connection request
    connect(_fdSocket, (struct sockaddr*)&_serverAddress,
            sizeof(_serverAddress));

    // sending data
    std::string message = "Hello, server!";
    send(_fdSocket, message.c_str(), message.size(), 0);
    //Create specific file descriptor for epoll calls
    _epfd = epoll_create(EPOLL_QUEUE_LEN);
  // Initialisation du tableau d'epoll_event pour chaque instance
  for (int i = 0; i < MAX_EPOLL_EVENTS_PER_RUN; ++i) {
    _ev[i].events = 0;
    _ev[i].data.fd = -1;
  }

  // Ajout du client socket à epoll
  struct epoll_event ev;
  ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
  ev.data.fd = _client_sock;
  int res = epoll_ctl(_epfd, EPOLL_CTL_ADD, _client_sock, &ev);

  while (1) {
    // Attente d'événements sur les sockets
    int nfds = epoll_wait(_epfd, _ev, MAX_EPOLL_EVENTS_PER_RUN, EPOLL_RUN_TIMEOUT);
    if (nfds < 0)
      std::cout << "Error in epoll_wait!" << std::endl;

    // Pour chaque socket prêt
    for (int i = 0; i < nfds; i++) {
      int fd = _ev[i].data.fd;
      handle_io_on_socket(fd);
    }
  }
}

Server::~Server() {
    if (_fdSocket >= 0) {
        close(_fdSocket);
        std::cout << "Socket " << _fdSocket << " closed.\n";
        close(_epfd);
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