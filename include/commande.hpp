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
    MODE,    // Commande pour définir un mode
    TOPIC,   // Commande pour définir un sujet de canal
    PART,    // Commande pour quitter un canal
    KICK,    // Commande pour expulser un utilisateur d'un canal
    INVITE,  // Commande pour inviter un utilisateur à un canal
    NOTICE   // Commande pour envoyer un avis
};

// Classe représentant une commande IRC
class commande {
    public:
        commande();
        ~commande();

};