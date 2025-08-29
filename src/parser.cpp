#include "../include/parser.hpp"


// Trouve l'index de fin d'une commande IRC (\r\n)
size_t parser::findEndOfCommand(const std::string& input) {
	return input.find("\r\n");
}



parser parser::parseIRCCommand(const std::string& input) {
	parser result;
	size_t end = parser::findEndOfCommand(input);
	std::string commandStr = (end != std::string::npos) ? input.substr(0, end) : input;
	std::istringstream iss(commandStr);
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

std::ostream& operator<<(std::ostream& os, parser message) {
	os << "input: " << message._input << std::endl;
	os << "command: " << message._command << std::endl;
	os << "arg: ";
	for (size_t i = 0; i < message._args.size(); ++i) {
		os << message._args[i];
		if (i != message._args.size() - 1) os << ", ";
	}
	os << std::endl;
	os << "trailing: " << message. _trailing << std::endl;
	return os;
}