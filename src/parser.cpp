#include <string>
#include <vector>
#include <sstream>
#include "../include/parser.hpp"


parser parser::parseIRCCommand(const std::string& input) {
	parser result;
	std::istringstream iss(input);
	std::string token;

	// Extraire la commande
	iss >> result._command;

	// Extraire les arguments jusqu'à ':' ou fin
	while (iss >> token) {
		if (token[0] == ':') {
			// Tout ce qui suit ':' est le trailing/message
			std::string rest;
			std::getline(iss, rest);
			result._trailing = token.substr(1) + rest;
			break;
		} else {
			result._args.push_back(token);
		}
	}
	return result;
}


/* parser::getFirstWord(std::string ) */
parser::parser() {}
parser::parser(const std::string& input) : _input(input) {

}
parser::~parser() {}
parser::parser(const std::string& cmd, const std::vector<std::string>& arguments, const std::string& trail)
	: _command(cmd), _args(arguments), _trailing(trail) {}