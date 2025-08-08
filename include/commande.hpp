#pragma once

enum commandeType {
    PASS,    // Commande pour envoyer un mot de passe
    NICK,    // Commande pour définir un pseudonyme
    USER,    // Commande pour définir un utilisateur
    JOIN,    // Commande pour rejoindre un canal
    PRIVMSG, // Commande pour envoyer un message privé
    QUIT,    // Commande pour quitter le serveur
    PING,    // Commande pour répondre à un ping
    PONG,    // Commande pour envoyer un pong
    PART,    // Commande pour quitter un canal
    NOTICE   // Commande pour envoyer un avis
};

/*    The commands which may only be used by channel operators are:

        KICK    - Eject a client from the channel
        MODE    - Change the channel's mode
        INVITE  - Invite a client to an invite-only channel (mode +i)
        TOPIC   - Change the channel topic in a mode +t channel
*/
enum operatorCommandeType {
    KICK,    // Commande pour expulser un utilisateur d'un canal
    MODE,    // Commande pour définir un mode
    INVITE,  // Commande pour inviter un utilisateur à un canal
    TOPIC,   // Commande pour définir un sujet de canal
};


/*    A channel operator is identified by the '@' symbol next to their
   nickname whenever it is associated with a channel (ie replies to the
   NAMES, WHO and WHOIS commands).
*/

// Classe représentant une commande IRC
class commande {
    public:
        commande();
        ~commande();

};