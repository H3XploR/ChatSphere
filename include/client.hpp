#pragma once
#include <string>
#include <unistd.h>
#include "server.hpp"
#include <vector>
#include "channel.hpp"

class Server;
class channel;
class client {
    public:
        client(std::string username);
        std::string                              _hostName;                 //the real name of the host that the client is running on
        std::string                                _userName;                 //the username of the client on that host
        std::string                                  _reference;                //any client can reference the channel using the name of the channel.
        std::list<std::pair<std::string, channel> >      _channelList;        //channel appartenants au client
        int                                              _fd;
        bool                                            _authorized;
/*         std::string             _input; peut-etre inutile*/
        std::string             getHostName();
        virtual ~client();


/* To allow a reasonable amount of order to be kept within the IRC
   network, a special class of clients (operators) is allowed to perform
   general maintenance functions on the network.  Although the powers
   granted to an operator can be considered as 'dangerous', they are
   nonetheless required.  Operators should be able to perform basic
   network tasks such as disconnecting and reconnecting servers as
   needed to prevent long-term use of bad network routing.  In
   recognition of this need, the protocol discussed herein provides for
   operators only to be able to perform such functions.  See sections
   4.1.7 (SQUIT) and 4.3.5 (CONNECT).

   A more controversial power of operators is the ability  to  remove  a
   user  from  the connected network by 'force', i.e. operators are able
   to close the connection between any client and server.   The
   justification for  this  is delicate since its abuse is both
   destructive and annoying.  For further details on this type of
   action, see section 4.6.1 (KILL).
   */

   /*The channel operator (also referred to as a "chop" or "chanop") on a
   given channel is considered to 'own' that channel. */


   /*Dans ma logic, la class operator herite de la class client 
     et obtient des pouvoir en plus (c'est comme un admin)*/

  // Méthodes spécifiques aux opérateurs
        void kickUser(const std::string& userName, const std::string& channelName);
        void banUser(const std::string& userName, const std::string& channelName);
        void setChannelMode(const std::string& channelName, const std::string& mode);
    private:
      client();
};

std::ostream& operator<<(std::ostream& os, const client& Client);