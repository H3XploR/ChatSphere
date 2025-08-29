#include "../include/server.hpp"

// Convertit une adresse IP binaire en format décimal (uint32_t)
uint32_t ipToDecimal(const sockaddr_in& addr) {
  std::cout << "ip to decimal: ";
  return ntohl(addr.sin_addr.s_addr);
}



/**
 * @brief Constructs a Server object, initializes and configures the server socket,
 *        binds it to the specified port, sets up epoll for event-driven I/O, and
 *        enters the main event loop to handle incoming connections and client I/O.
 *
 * The constructor performs the following steps:
 * - Creates a non-blocking TCP socket.
 * - Binds the socket to INADDR_ANY and the specified port.
 * - Starts listening for incoming connections.
 * - Initializes the epoll file descriptor and event array.
 * - Adds the server socket to the epoll instance.
 * - Enters an infinite loop to:
 *   - Wait for events using epoll_wait.
 *   - Accept new client connections and add them to epoll.
 *   - Handle I/O events on client sockets.
 *
 * @throws std::runtime_error if socket creation, binding, or listening fails.
 */
Server::Server() : _fdSocket(socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)), _port(8080) {
    std::cout << "server loading....\n";
    std::cout << "fd_socket: " << _fdSocket << "\n";
    if (_fdSocket < 0)
        throw std::runtime_error("socket creation failed");
    // specifying address
    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_port = htons(_port);
    _serverAddress.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to the address
    if (bind(_fdSocket, (struct sockaddr*)&_serverAddress, sizeof(_serverAddress)) < 0)
        throw std::runtime_error("bind failed");
    std::cout << "IP: " << ipToDecimal(this->_serverAddress) << std::endl;
    std::cout << "Port: " << this->_port << std::endl;
    // listen for incoming connections
    if (listen(_fdSocket, SOMAXCONN) < 0)
        throw std::runtime_error("listen failed");

    //Create specific file descriptor for epoll calls
    _epfd = epoll_create(EPOLL_QUEUE_LEN);
    // Initialisation du tableau d'epoll_event pour chaque instance
    for (int i = 0; i < MAX_EPOLL_EVENTS_PER_RUN; ++i) {
        _ev[i].events = 0;
        _ev[i].data.fd = -1;
    }

    // Ajout du serveur socket à epoll
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
    ev.data.fd = _fdSocket;

    int res = epoll_ctl(_epfd, EPOLL_CTL_ADD, _fdSocket, &ev);
    (void)res;
    while (1) {
        // Attente d'événements sur les sockets
        int nfds = epoll_wait(_epfd, _ev, MAX_EPOLL_EVENTS_PER_RUN, EPOLL_RUN_TIMEOUT);
        if (nfds < 0)
            std::cout << "Error in epoll_wait!" << std::endl;

        // Pour chaque socket prêt
        for (int i = 0; i < nfds; i++) {
            int fd = _ev[i].data.fd;
            if (fd == _fdSocket) {
                // Accept new connection
                sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_sock = accept(_fdSocket, (struct sockaddr*)&client_addr, &client_len);
                if (client_sock >= 0) {
                    struct epoll_event client_ev;
                    client_ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
                    client_ev.data.fd = client_sock;
                    epoll_ctl(_epfd, EPOLL_CTL_ADD, client_sock, &client_ev);
                    std::cout << "New client connected: " << client_sock << std::endl;
                    // Créer le nouveau client
                    _client.push_back(std::make_pair(client_sock, client("nouveau client")));
                }
            } else {
                // Handle IO on client sockets only
                handle_io_on_socket(fd);
            }
        }
    }
}

void  Server::handle_io_on_socket(int fd) {
  size_t size = 1084;
  std::string buf(size, '\0');
  ssize_t bytes_received = recv(fd, &buf[0], buf.size(), MSG_DONTWAIT);
  if (bytes_received > 0) {
    buf.resize(bytes_received); // Resize to actual data received
    std::cout << buf << std::endl;
    for (std::list<std::pair<int, client> >::iterator it = _client.begin(); it != _client.end(); ++it) {
      if (it->first == fd) {
        // You now have an iterator 'it' pointing to the client with socket 'fd'
        // You can access the client object via it->second
        parser input_parsed = parser::parseIRCCommand(buf);
        std::cout << "input parsed: " << input_parsed;
        handle_command(input_parsed);
        break;
      }
    }


  }
}

void    Server::handle_command(parser parsed_command) {
        std::string command[10];
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

std::ostream& operator<<(std::ostream& os, const Server& server) {
    os << "IP: " << ipToDecimal(server._serverAddress) << std::endl;
    os << "Port: " << server._port << std::endl;
    return os;
}