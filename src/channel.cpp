#include "../include/channel.hpp"
/*CANONIC COPLIEN*/

channel::channel() : _name("<clientHostname>'s_server") {

}

channel::~channel() {

}

/*
   Channels names are strings (beginning with a '&' or '#' character) of
   length up to 200 characters.  Apart from the the requirement that the
   first character being either '&' or '#'; the only restriction on a
   channel name is that it may not contain any spaces (' '), a control G
   (^G or ASCII 7), or a comma (',' which is used as a list item
   separator by the protocol).
*/
bool channel::checkName() {
    if (_name.empty())
        return false;
    if (_name.length() > 200)
        return false;

    char    firstChar = _name.at(0);
    if (firstChar != '#' && firstChar != '&')
        return false;

//check forbidden character
    std::string forbidden = " \a,";
    for (size_t i = 0; i < forbidden.size(); ++i) {
        if (_name.find(forbidden[i]) != std::string::npos)
            return false;
    }
//---------------------------------------------------------
    return true;
}
//WE MUST MAKE A TESTER FOR THAT (LUCAS IF U SEE THAT  :))))