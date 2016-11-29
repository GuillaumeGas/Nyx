#include "Token.hpp"

using namespace std;

Token::Token (TokenType type, const string & value, location_t loc) : type (type), value (value), loc (loc), eof (false) {}

Token Token::make (const std::string & value, location_t loc) {
    TokenType ttype = Token::getFromStr (value);
    return Token (ttype, value, loc);
}

Token Token::makeEof () {
    Token t = Token (_EOF_, "EOF", {0, 0});
    t.eof = true;
    return t;
}

string Token::toString() const {
    string type = Token::getType (this->type);
    return "<" + type + "(" + value + "), loc(" + std::to_string(loc.line) + ", " + std::to_string(loc.column) + ")>";
}

bool Token::isEof() const {
    return this->eof;
}

location_t Token::getLocation () const {
    return this->loc;
}
