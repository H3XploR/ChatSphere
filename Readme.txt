ChatSphere est une implémentation personnalisée d'un serveur de chat basé sur le protocole Internet Relay Chat (IRC). L'objectif principal de ce projet est de créer un serveur de chat fonctionnel qui permet à plusieurs utilisateurs de communiquer en temps réel via différents canaux et messages privés.
Voici quelques caractéristiques clés de ChatSphere :


Protocole IRC : Utilisation du protocole IRC, un standard bien établi pour la communication en temps réel sur Internet.


Gestion des Utilisateurs : Capacité à gérer plusieurs connexions utilisateur simultanément, permettant à chacun de rejoindre des canaux et d'envoyer des messages.


Canaux de Discussion : Création et gestion de différents canaux de discussion où les utilisateurs peuvent interagir.


Messages Privés : Possibilité pour les utilisateurs d'envoyer des messages privés à d'autres utilisateurs connectés au serveur.


Commandes IRC : Implémentation des commandes IRC standard pour permettre aux utilisateurs de naviguer et d'interagir avec le serveur de manière efficace.


Sécurité et Authentification : Mécanismes de base pour l'authentification des utilisateurs et la gestion des permissions au sein des canaux.


Ce projet offre une excellente opportunité de comprendre les concepts de la communication réseau, la gestion des sockets, et l'implémentation des protocoles de communication en temps réel.
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                                                                                                    Extrait SUJET:
Vous n’avez pas à développer un client.
Vous ne devez pas gérer la communication de serveur à serveur

Votre binaire devra être appelé comme ceci :
./ircserv <port> <password>

port : Le numéro du port sur lequel votre serveur acceptera les connexions en-
trantes.

password : Le mot de passe permettant de s’identifier auprès de votre serveur
IRC, et qui devra être fourni par tout client IRC souhaitant s’y connecter


                                                                Fonctions externes autorisées:

                                                            Tout ce qui respecte la norme C++ 98.

                                                            socket, close, setsockopt, getsockname,
                                                            getprotobyname, gethostbyname, getaddrinfo,
                                                            freeaddrinfo, bind, connect, listen, accept, htons,
                                                            htonl, ntohs, ntohl, inet_addr, inet_ntoa, send,
                                                            recv, signal, sigaction, lseek, fstat, fcntl, poll
                                                            select, kqueue ,epoll

III.1 Prérequis
• Le serveur doit pouvoir gérer plusieurs clients simultanément sans jamais bloquer.
• Le forking est interdit. Toute les opérations entrées/sorties doivent être non blo-
quantes.
• Vous n’avez le droit qu’à un seul poll() (ou équivalent) pour gérer toutes ces
opérations (read, write, mais aussi listen, etc.).
Comme vous pouvez utiliser des FD en mode non bloquant, il est
possible d’avoir un serveur non bloquant avec read/recv ou write/send
tout en n’ayant pas recours à poll() (ou équivalent).
Mais cela consommerait des ressources système inutilement.
Ainsi, si vous essayez d’utiliser read/recv ou write/send avec
n’importe quel FD sans utiliser poll() (ou équivalent), votre note
sera de 0.
• Il existe plusieurs clients IRC. Vous devez choisir l’un d’eux comme référence.
Votre client de référence sera utilisé pour l’évaluation.
• Votre client de référence doit pouvoir se connecter à votre serveur sans rencontrer
d’erreur.
• La communication entre le client et le serveur se fera en TCP/IP (v4 ou v6).
• Utiliser votre client de référence avec votre serveur devra être similaire à l’utiliser
avec un serveur IRC officiel. Cependant, seules les fonctionnalités suivantes sont
obligatoires :
◦ Vous devez pouvoir vous authentifier, définir un nickname, un username, re-
joindre un channel, envoyer et recevoir des messages privés, avec votre client
de référence.
◦ Tous les messages envoyés par un client dans un channel doivent être transmis
à tous les clients ayant rejoint ce channel.
◦ Vous devez avoir des operators et des utilisateurs basiques.
◦ Vous devez donc implémenter les commandes spécifiques aux operateurs de
canaux.
◦ KICK - Ejecter un client du channel
◦ INVITE - Inviter un client au channel
◦ TOPIC - Modifier ou afficher le thème du channel
◦ MODE - Changer le mode du channel :
— i : Définir/supprimer le canal sur invitation uniquement
6
ft_irc Internet Relay Chat
— t : Définir/supprimer les restrictions de la commande TOPIC pour les opé-
rateurs de canaux
— k : Définir/supprimer la clé du canal (mot de passe)
— o : Donner/retirer le privilège de l’opérateur de canal
— l : Définir/supprimer la limite d’utilisateurs pour le canal
• Bien entendu, on attend de vous un code propre.


III.2 Pour MacOS seulement
Vu que MacOS n’implémente pas write() comme les autres Unix, vous
pouvez utiliser fcntl().
Vous devez utiliser des descripteurs de fichier en mode non bloquant
afin d’obtenir un résultat similaire à celui des autres Unix.
Toutefois, vous ne pouvez utiliser fcntl() que de la façon suivante :
fcntl(fd, F_SETFL, O_NONBLOCK);
Tout autre flag est interdit.
III.3 Exemple de test
Vérifiez absolument toutes les erreurs et tous les problèmes possibles (donnée partiel-
lement reçue, bande passante faible, etc.).
Afin de vous assurer que votre serveur traite tout ce que vous lui envoyez, voici un
test basique qui peut être fait avec nc :
\$> nc 127.0.0.1 6667
com^Dman^Dd
\$>
Utilisez ctrl+D pour envoyer la commande en plusieurs parties : ’com’, puis ’man’,
puis ’d\n’.
Afin de traiter une commande, vous devez en premier lieu la reconstituer en concaté-
nant les paquets reçus.
