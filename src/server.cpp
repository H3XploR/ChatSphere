#include "../include/server.hpp"

// Squelettes des handlers de commandes IRC

void Server::handle_pass(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    std::cout << "handle_pass called" << std::endl;
    if (cmd._args.empty()) {
        std::cout << "argument manquant\n";
        return ;
    }
    if (cmd._args.at(0) == _password) {
        send_to_fd("good password!\n", fd);
        leclient._authorized = true; // Marque le client comme autorisé
    } else {
        send_to_fd("bad password!\n", fd);
        leclient._authorized = false; // Refuse l'autorisation
    }
}

void Server::send_to_fd(std::string message, int fd) {
    if (send(fd, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Failed to send message to fd " << fd << std::endl;
    }
}

void Server::handle_nick(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    std::cout << "handle_nick called" << std::endl;
    if (cmd._args.empty() && cmd._trailing.empty()) {
        send_to_fd("arguments manquants\n", fd);
        return;
    }
    else if(!cmd._args.empty())
        leclient._userName = cmd._args.at(0);
    else
        leclient._userName = cmd._trailing;
    send_to_fd("client changed\n", fd);
}


void Server::handle_user(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    (void)leclient;
    (void)cmd;
    std::cout << "handle_user called" << std::endl;
}


void Server::handle_join(const parser& cmd, client& leclient, int fd) {
    std::string channelName;
    if (!cmd._args.empty())
        channelName = cmd._args[0];
    else if (!cmd._trailing.empty())
        channelName = cmd._trailing;
    else {
        send_to_fd("Error: JOIN requires a channel name\r\n", fd);
        return;
    }

    // Vérifier le nom du channel
    channel tempChannel;
    tempChannel._name = channelName;
    if (!tempChannel.checkName()) {
        send_to_fd("Error: Invalid channel name\r\n", fd);
        return;
    }

    // Chercher si le channel existe déjà
    channel* foundChannel = NULL;
    for (size_t i = 0; i < _channel.size(); ++i) {
        if (_channel[i]._name == channelName) {
            foundChannel = &_channel[i];
            break;
        }
    }
    if (!foundChannel) {
        createNewChannel(channelName);
        foundChannel = &_channel.back();
        send_to_fd("Channel created and joined: " + channelName + "\r\n", fd);
    } else {
        send_to_fd("Joined channel: " + channelName + "\r\n", fd);
    }

    // Ajouter le client au channel
    foundChannel->_client.push_back(leclient);
    // Ajouter le channel à la liste du client
    leclient._channelList.push_back(std::make_pair(channelName, *foundChannel));

    std::cout << "Client joined channel: " << channelName << std::endl;
    
}


void Server::handle_privmsg(const parser& cmd, client& leclient, int fd) {
    std::string target;
    std::string message;
    if (!cmd._args.empty())
        target = cmd._args[0];
    else if (!cmd._trailing.empty())
        target = cmd._trailing;
    else {
        send_to_fd("Error: PRIVMSG requires a target\r\n", fd);
        return;
    }

    // Le message est dans _trailing
    if (cmd._args.size() > 1)
        message = cmd._args[1];
    else
        message = cmd._trailing;

    if (message.empty()) {
        send_to_fd("Error: PRIVMSG requires a message\r\n", fd);
        return;
    }

    // Trouver le channel cible
    channel* foundChannel = NULL;
    for (size_t i = 0; i < _channel.size(); ++i) {
        if (_channel[i]._name == target) {
            foundChannel = &_channel[i];
            break;
        }
    }
    if (!foundChannel) {
        send_to_fd("Error: Channel not found\r\n", fd);
        return;
    }

    // Envoyer le message à tous les clients du channel
    for (size_t i = 0; i < foundChannel->_client.size(); ++i) {
        int client_fd = foundChannel->_client[i]._fd;
        send_to_fd(leclient._userName + " PRIVMSG " + target + " :" + message + "\r\n", client_fd);
    }
    std::cout << "PRIVMSG sent to channel " << target << ": " << message << std::endl;
}


void Server::handle_part(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    (void)leclient;
    (void)cmd;
    std::cout << "handle_part called" << std::endl;
}


void Server::handle_quit(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    (void)leclient;
    (void)cmd;
    std::cout << "handle_quit called" << std::endl;
}


void Server::handle_kick(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    (void)leclient;
    (void)cmd;
    std::cout << "handle_kick called" << std::endl;
}


void Server::handle_invite(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    (void)leclient;
    (void)cmd;
    std::cout << "handle_invite called" << std::endl;
}


void Server::handle_topic(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    (void)leclient;
    (void)cmd;
    std::cout << "handle_topic called" << std::endl;
}


void Server::handle_mode(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    (void)leclient;
    (void)cmd;
    std::cout << "handle_mode called" << std::endl;
}


void Server::handle_names(const parser& cmd, client& leclient, int fd) {
    (void)fd;
    (void)leclient;
    (void)cmd;
    std::cout << "handle_names called" << std::endl;
}

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
Server::Server(std::string password) : _fdSocket(socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)), _port(8080), _password(password) {
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
                    _client.back().second._fd = client_sock;
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
        handle_command(input_parsed, it->second, fd);
        break;
      }
    }


  }
}

void Server::handle_command(parser& parsed_command, client& leclient, int fd) {
        std::string command[12] = {
            "PASS",
            "NICK",
            "USER",
            "JOIN",
            "PRIVMSG",
            "PART",
            "QUIT",
            "KICK",
            "INVITE",
            "TOPIC",
            "MODE",
            "NAMES"
        };
        typedef void (Server::*CommandHandler)(const parser&, client&, int);
        CommandHandler handlers[12] = {
            &Server::handle_pass,
            &Server::handle_nick,
            &Server::handle_user,
            &Server::handle_join,
            &Server::handle_privmsg,
            &Server::handle_part,
            &Server::handle_quit,
            &Server::handle_kick,
            &Server::handle_invite,
            &Server::handle_topic,
            &Server::handle_mode,
            &Server::handle_names
        };

        for (int i = 0; i < 12; ++i) {
            if (parsed_command._command == command[i]) {
                if (i == 0)
                    (this->*handlers[i])(parsed_command, leclient, fd);
                else {
                    if (leclient._authorized == true)
                        (this->*handlers[i])(parsed_command, leclient, fd);
                    else
                        std::cout << "client non authorise, un mot de passe est requie pour se connecter et faire des commandes\n"; 
                }
                break;
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
    channel newChannel;
    newChannel._name = channelName;
    _channel.push_back(newChannel);
}

std::ostream& operator<<(std::ostream& os, const Server& server) {
    os << "IP: " << ipToDecimal(server._serverAddress) << std::endl;
    os << "Port: " << server._port << std::endl;
    return os;
}