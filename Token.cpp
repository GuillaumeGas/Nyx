#include "Token.hpp"

using namespace std;

TokenIntValue::TokenIntValue(int i) : value(i){}
TokenCharValue::TokenCharValue(char c) : value(c) {} 
TokenStringValue::TokenStringValue(string& s) : value(s) {}

string TokenIntValue::to_string() const { return string("42"); }
string TokenCharValue::to_string() const { return string("43"); }
string TokenStringValue::to_string() const { return string(value); }

Token::Token(TokenType t, int v, unsigned int l) {
  type = t;
  value = new TokenIntValue(v);
  line = l;
}

Token::Token(TokenType t, char c, unsigned int l) {
  type = t;
  value = new TokenCharValue(c);
  line = l;
}

Token::Token(TokenType t, string& s, unsigned int l) {
  type = t;
  value = new TokenStringValue(s);
  line = l;
}

Token::~Token() { if (value) { delete value; } }

string Token::to_string() const {
  string res = "[Type = ";
  res += tokenType_to_string() + ", Value = " + value->to_string() + ", Line : 0]";
  return res;
}

string Token::tokenType_to_string() const {
  string res;
  switch (type) {
  case NUM:
    res = "NUM";
    break;
  case IDENT:
    res = "IDENT";
    break;
  case TYPE:
    res = "TYPE";
    break;
  case ASSIGN:
    res = "ASSIGN";
    break;
  case SEMICOLON:
    res = "SEMICOLON";
    break;
  default:
    res = "ERR";
  }
  return res;
}

Token* Token::create(string& token, unsigned int line) {
  if(Token::is_type(token)) {
    return new Token(TokenType::TYPE, token, line);
  } else if(Token::is_ident(token)) {
    return new Token(TokenType::IDENT, token, line);
  } else if(Token::is_assign(token)) {
    return new Token(TokenType::ASSIGN, token, line);
  } else if(Token::is_number(token)) {
    return new Token(TokenType::NUM, token, line);
  } else if(Token::is_semicolon(token)) {
    return new Token(TokenType::SEMICOLON, token, line);
  } else {
    cout << "[Error] Unknown token." << endl;
  }
}

bool Token::is_type(string& t) {
  if(t == "int") {
    return true;
  } else {
    return false;
  }
}

bool Token::is_ident(string& t) {
  if((t[0] >= 'A' && t[0] <= 'Z') || (t[0] >= 'a' && t[0] <= 'z')) {
    return true;
  } else {
    return false;
  }
} 

bool Token::is_assign(string& t) {
  return t == "=";
}

bool Token::is_number(string& t) {
  bool res = true;
  int i = 0;
  while (i < t.size() && res) {
    if(t[i] < '0' || t[i] > '9') {
      res = false;
    } 
    i++;
  }
  return res;
}

bool Token::is_semicolon(string& t) {
  return t == ";";
}
    
