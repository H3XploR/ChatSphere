#include <sys/socket.h>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include "../include/channel.hpp"
#include "../include/client.hpp"
//Chercher un moyen de retourner un file descriptor avec socket

/* static  bool    checkBool(bool ret) {
    if (ret == true)
        std::cout << "true\n";
    else
        std::cout << "false\n";
    return ret;
} */

int main(void) {

/*socket: Test au hasard*/
    int domain = 7;
    int type = 8;
    int protocol = 5;
    int file_descriptor = socket(domain, type, protocol); // retourne -1
    std::cout << file_descriptor << std::endl;

    domain = AF_UNIX; //Local communication | voir pour ipv4 et ipv6
    type = SOCK_STREAM | SOCK_NONBLOCK; //tcp enfin je crois a confirmer et pour rendre non bloquant
    protocol = 0;
    file_descriptor = socket(domain, type, protocol); // retourne un fd socket
    std::cout << file_descriptor << std::endl;
    close(file_descriptor);
//--------------------------------TESTING client------function------------------------------------
    client clientTestHostName("Calus");
    std::cout << clientTestHostName;
//--------------------------------TESTING checkName() function-----------A FINIR-------------------------
//should be true
    std::cout << "testing checkName channels function\n";
    //channel channelTest; /*should not compile*/
    //checkBool(channelTest.checkName()); /* should be false */
    return 0;
}
