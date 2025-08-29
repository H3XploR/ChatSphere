#include "../include/parser.hpp"
#include <sys/socket.h>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include "../include/channel.hpp"
#include "../include/client.hpp"
#include "../include/parser.hpp"
#include "../include/server.hpp"
#include <istream>
static void test_parser_basic() {
    parser p = parser::parseIRCCommand("JOIN #general");
    std::cout << "Test JOIN: " << (p._command == "JOIN" && p._args.size() == 1 && p._args[0] == "#general" && p._trailing.empty() ? "OK" : "FAIL") << std::endl;
}

static void test_parser_privmsg() {
    parser p = parser::parseIRCCommand("PRIVMSG yanni :hello world");
    std::cout << "Test PRIVMSG: " << (p._command == "PRIVMSG" && p._args.size() == 1 && p._args[0] == "yanni" && p._trailing == "hello world" ? "OK" : "FAIL") << std::endl;
}

static void test_parser_multiple_args() {
    parser p = parser::parseIRCCommand("MODE #chan +o yanni");
    std::cout << "Test MODE: " << (p._command == "MODE" && p._args.size() == 3 && p._args[0] == "#chan" && p._args[1] == "+o" && p._args[2] == "yanni" && p._trailing.empty() ? "OK" : "FAIL") << std::endl;
}

static void test_parser_trailing_spaces() {
    parser p = parser::parseIRCCommand("TOPIC #chan :This is the topic with spaces");
    std::cout << "Test TOPIC: " << (p._command == "TOPIC" && p._args.size() == 1 && p._args[0] == "#chan" && p._trailing == "This is the topic with spaces" ? "OK" : "FAIL") << std::endl;
}

//j'utilise mIRC pour tester le server avec un client
static void test_creating_server() {
    std::cout << "\n\n\n\n\n\ntest creation de server\n";
    Server irc_server;
}


//Chercher un moyen de retourner un file descriptor avec socket

/* static  bool    checkBool(bool ret) {
    if (ret == true)
        std::cout << "true\n";
    else
        std::cout << "false\n";
    return ret;
} */


int main(void) {
    // ----------- TESTS UNITAIRES DU PARSER -----------
    test_parser_basic();
    test_parser_privmsg();
    test_parser_multiple_args();
    test_parser_trailing_spaces();

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

/*
    PAS COMPRIS LE ISTREAM MAIS OK
*/
/*     std::cout << "test manip string\n";
    std::istream index;
    std::string phrase = std::string("The class template basic_string stores and manipulates sequences ") +
                        "of character-like objects, which are non-array objects of TrivialType" +
                        "and StandardLayoutType. The class is dependent neither on the character " +
                        "type nor on the nature of operations on that type. The definitions of" +
                        " the operations are supplied via the Traits template parameter";
    std::cout << index << std::endl;
    index << phrase;
    std::cout << index << std::endl; */
    //--------------------------------TESTING Parser---------------------------------
    test_parser_basic();
    test_parser_privmsg();
    test_parser_multiple_args();
    test_parser_trailing_spaces();
    test_creating_server();
    return 0;
}
