#pragma once
#include "client.hpp"
#include <string>
#include <vector>

/*
# : Channel global, accessible à tous les serveurs du réseau IRC.
& : Channel local, uniquement accessible sur le serveur où il a été créé.
*/
enum class TYPE_SERVER {
    DISTRUBUTED
};

class client;

class channel {
    /*A channel is a named group of one or more clients which will all
   receive messages addressed to that channel.*/
    public:
    std::string              _message;
    std::vector<client>      _client;
    std::string              _name; //Channels names are strings (beginning with a '&' or '#' character) of length up to 200 characters.
    std::vector<std::string> _operator;
    std::string              _operatorPassword;
    std::string              _topic; //sujet/theme du channel
    std::string              _mode;
    std::string				 _channelPassword;
    int                      _user_limit;
    /*
     There are two types of channels allowed by this protocol.  One is a
   distributed channel which is known to all the servers that are connected to the network.
   THE OTHER IS I DONT KNOW FOR THE MOMENT (A FOUILLE)
    */
    int                 _type;
    bool                checkName();
    /*
        Faire en sorte que le nom du channel par default soit 
                    "<nomDuCreateur>'s server"
    */
    ~channel();
    private:
        channel(); 
};