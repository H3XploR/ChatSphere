#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cstddef>
#include <sstream>
enum commandType {
    PASS,    // Commande pour envoyer un mot de passe
    NICK,    // Commande pour définir un pseudonyme
    USER,    // Commande pour définir un utilisateur
    JOIN,    // Commande pour rejoindre un canal
    PRIVMSG, // Commande pour envoyer un message privé
    QUIT,    // Commande pour quitter le serveur
    PING,    // Commande pour répondre à un ping
    PONG,    // Commande pour envoyer un pong
    PART,    // Commande pour quitter un canal
    NOTICE,   // Commande pour envoyer un avis
    KICK,    // Commande pour expulser un utilisateur d'un canal
    MODE,    // Commande pour définir un mode
    INVITE,  // Commande pour inviter un utilisateur à un canal
    TOPIC,   // Commande pour définir un sujet de canal
};

/*    The commands which may only be used by channel operators are:

        KICK    - Eject a client from the channel
        MODE    - Change the channel's mode
        INVITE  - Invite a client to an invite-only channel (mode +i)
        TOPIC   - Change the channel topic in a mode +t channel
*/


/*    A channel operator is identified by the '@' symbol next to their
   nickname whenever it is associated with a channel (ie replies to the
   NAMES, WHO and WHOIS commands).
*/


/* class parser {
    public:
        parser(std::string message);
        detectCommand();
        
        std::string _message;
    private:
        parser();


}; */

// Classe représentant une commande IRC
// Structure représentant une commande IRC parsée
// command : le nom de la commande (ex : JOIN, PRIVMSG...)
// args    : les arguments de la commande (ex : nom du channel, destinataire...)
// trailing: le message ou paramètre après le caractère ':' (souvent le texte d'un message)
// Le trailing est tout ce qui suit le premier ':' dans une commande IRC. Il sert généralement à transmettre un texte libre (ex : le contenu d'un message, le topic d'un channel, etc.)
class parser {
public:
    std::string _input;
	std::string _command;              // Nom de la commande IRC
	std::vector<std::string> _args;    // Arguments de la commande
	std::string _trailing;             // Partie "trailing" (texte après ':')
    static parser parseIRCCommand(const std::string& input);
    static size_t findEndOfCommand(const std::string& input);
    parser(const std::string& input);
	//parser(const std::string& cmd, const std::vector<std::string>& arguments, const std::string& trail);
    parser(const std::string& cmd, const std::vector<std::string>& arguments, const std::string& trail);
    parser();
    ~parser();

};

std::ostream& operator<<(std::ostream& os, parser message);