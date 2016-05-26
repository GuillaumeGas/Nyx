#include "Token.hpp"

using namespace std;
using namespace bob;

TokenIntValue::TokenIntValue(int i) : value(i){}
TokenCharValue::TokenCharValue(char c) : value(c) {} 
TokenStringValue::TokenStringValue(string& s) : value(s) {}

string TokenIntValue::to_string() const { return std::to_string(value); }
string TokenCharValue::to_string() const { return std::to_string(value); }
string TokenStringValue::to_string() const { return value; }

Token::Token(TokenType t, int v, unsigned int l, unsigned int col) {
  type = t;
  value = new TokenIntValue(v);
  line = l;
  column = col;
}

Token::Token(TokenType t, char c, unsigned int l, unsigned int col) {
  type = t;
  value = new TokenCharValue(c);
  line = l;
  column = col;
}

Token::Token(TokenType t, string& s, unsigned int l, unsigned int col) {
  type = t;
  value = new TokenStringValue(s);
  line = l;
  column = col;
}

Token::~Token() { if (value) { delete value; } }

string Token::to_string() const {
  string res = "[Type = ";
  res += type_to_string() + ", Value = " + value->to_string() + ", Line : " + std::to_string(line)  + ", Column : " + std::to_string(column) + "]";
  return res;
}

string Token::type_to_string() const {
  string res;
  switch (type) {
  case INT:
    res = "INT";
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
  case CHAR:
    res = "CHAR";
    break;
  case STRING:
    res = "STRING";
    break;
  case PLUS:
    res = "PLUS";
    break;
  case PLUSPLUS:
    res = "PLUSPLUS";
    break;
  case PLUSEQ:
    res = "PLUSEQ";
    break;
  case MINUS:
    res = "MINUS";
    break;
  case MINUSMINUS:
    res = "MINUSMINUS";
    break;
  case MINUSEQ:
    res = "MINUSEQ";
  case MUL:
    res = "MUL";
    break;
  case MULEQ:
    res = "MULEQ";
    break;
  case DIV:
    res = "DIV";
    break;
  case DIVEQ:
    res = "DIVEQ";
    break;
  case MOD:
    res = "MOD";
    break;
  case MODEQ:
    res = "MODEQ";
    break;
  case LT:
    res = "LT";
    break;
  case LE:
    res = "LE";
    break;
  case GT:
    res = "GT";
    break;
  case GE:
    res = "GE";
    break;
  case EQ:
    res = "EQ";
    break;
  case NE:
    res = "NE";
    break;
  case PAR_L:
    res = "PAR_L";
    break;
  case PAR_R:
    res = "PAR_R";
    break;
  case ACCOL_L:
    res = "ACCOL_L";
    break;
  case ACCOL_R:
    res = "ACCOL_R";
    break;
  case IF:
    res = "IF";
    break;
  case ELSE:
    res = "ELSE";
    break;
  case ELSEIF:
    res = "ELSEIF";
    break;
  case WHILE:
    res = "WHILE";
    break;
  case DO:
    res = "DO";
    break;
  case FOR:
    res = "FOR";
    break;
  case PRINT_I:
    res = "PRINT_I";
    break;
  case PRINT_S:
    res = "PRINT_S";
    break;
  case SCAN_I:
    res = "SCAN_I";
    break;
  case SCAN_S:
    res = "SCAN_S";
    break;
  case TRUE:
    res = "TRUE";
    break;
  case FALSE:
    res = "FALSE";
    break;
  case RETURN:
    res = "RETURN";
    break;
  default:
    res = "ERR";
  }
  return res;
}

Token* Token::create(string& token, unsigned int line, unsigned int col) {
  if(Token::is_if(token)) {
    return new Token(TokenType::IF, token, line, col);
  } else if(Token::is_else(token)) {
    return new Token(TokenType::ELSE, token, line, col);
  } else if(Token::is_elseif(token)) {
    return new Token(TokenType::ELSEIF, token, line, col);
  } else if(Token::is_while(token)) {
    return new Token(TokenType::WHILE, token, line, col);
  } else if(Token::is_do(token)) {
    return new Token(TokenType::DO, token, line, col);
  } else if(Token::is_for(token)) {
    return new Token(TokenType::FOR, token, line, col);
  } else if(Token::is_print_i(token)) {
    return new Token(TokenType::PRINT_I, token, line, col);
  } else if(Token::is_true(token)) {
    return new Token(TokenType::TRUE, token, line, col);
  } else if(Token::is_false(token)) {
    return new Token(TokenType::FALSE, token, line, col);
  } else if(Token::is_print_s(token)) {
    return new Token(TokenType::PRINT_S, token, line, col);
  } else if(Token::is_scan_i(token)) {
    return new Token(TokenType::SCAN_I, token, line, col);
  } else if(Token::is_scan_s(token)) {
    return new Token(TokenType::SCAN_S, token, line, col);
  } else if(Token::is_type(token)) {
    return new Token(TokenType::TYPE, token, line, col);
  } else if(Token::is_return(token)) {
    return new Token(TokenType::RETURN, token, line, col);
  } else if(Token::is_ident(token)) {
    return new Token(TokenType::IDENT, token, line, col);
  } else if(Token::is_assign(token)) {
    return new Token(TokenType::ASSIGN, token, line, col);
  } else if(Token::is_integer(token)) {
    return new Token(TokenType::INT, std::stoi(token), line, col);
  } else if(Token::is_semicolon(token)) {
    return new Token(TokenType::SEMICOLON, token, line, col);
  } else if(Token::is_char(token)) {
    return new Token(TokenType::CHAR, token.at(1), line, col);
  } else if(Token::is_string(token)) {
    string tok = token.erase(0, 1);
    tok = tok.erase(tok.size()-1, 1);
    return new Token(TokenType::STRING, tok, line, col);
  } else if(Token::is_plus(token)) {
    return new Token(TokenType::PLUS, token, line, col);
  } else if(Token::is_plusplus(token)) {
    return new Token(TokenType::PLUSPLUS, token, line, col);
  } else if(Token::is_pluseq(token)) {
    return new Token(TokenType::PLUSEQ, token, line, col);
  } else if(Token::is_minus(token)) {
    return new Token(TokenType::MINUS, token, line, col);
  } else if(Token::is_minusminus(token)) {
    return new Token(TokenType::MINUSMINUS, token, line, col);
  } else if(Token::is_minuseq(token)) {
    return new Token(TokenType::MINUSEQ, token, line, col);
  } else if(Token::is_mul(token)) {
    return new Token(TokenType::MUL, token, line, col);
  } else if(Token::is_muleq(token)) {
    return new Token(TokenType::MULEQ, token, line, col);
  } else if(Token::is_div(token)) {
    return new Token(TokenType::DIV, token, line, col);
  } else if(Token::is_diveq(token)) {
    return new Token(TokenType::DIVEQ, token, line, col);
  } else if(Token::is_mod(token)) {
    return new Token(TokenType::MOD, token, line, col);
  } else if(Token::is_modeq(token)) {
    return new Token(TokenType::MODEQ, token, line, col);
  } else if(Token::is_lt(token)) {
    return new Token(TokenType::LT, token, line, col);
  } else if(Token::is_le(token)) {
    return new Token(TokenType::LE, token, line, col);
  } else if(Token::is_gt(token)) {
    return new Token(TokenType::GT, token, line, col);
  } else if(Token::is_ge(token)) {
    return new Token(TokenType::GE, token, line, col);
  } else if(Token::is_eq(token)) {
    return new Token(TokenType::EQ, token, line, col);
  } else if(Token::is_ne(token)) {
    return new Token(TokenType::NE, token, line, col);
  } else if(Token::is_par_l(token)) {
    return new Token(TokenType::PAR_L, token, line, col);
  } else if(Token::is_par_r(token)) {
    return new Token(TokenType::PAR_R, token, line, col);
  } else if(Token::is_accol_l(token)) {
    return new Token(TokenType::ACCOL_L, token, line, col);
  } else if(Token::is_accol_r(token)) {
    return new Token(TokenType::ACCOL_R, token, line, col);
  } else {
    return NULL;
  }
}

bool Token::is_type(string& t) {
  if(t == "int" || t == "bool" || t == "char") {
    return true;
  } else {
    return false;
  }
}

bool Token::is_ident(string& t) {
  bool res = true;
  int i = 0;
  if((t[0] < 'A' || (t[0] > 'Z' && t[0] < 'a') || t[0] > 'z') && t[0] != '_') {
    res = false;
  }
  while(i < t.size() && res) {
    if(!((t[i] >= 'A' && t[i] <= 'Z') || (t[i] >= 'a' && t[i] <= 'z') || t[i] == '_')) {
      res = false;
    }
    i++;
  }
  return res;
} 

bool Token::is_assign(string& t) {
  return t == "=";
}

bool Token::is_integer(string& t) {
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

bool Token::is_char(string& t) {
  return t.size() == 3 && t[0] == '\'' && t[2] == '\'';
}

bool Token::is_string(string& t) {
  return t[0] == '"' && t[t.size()-1] == '"';
}

bool Token::is_plus(string& t) {
  return t == "+";
}

bool Token::is_plusplus(string& t) {
  return t == "++";
}

bool Token::is_pluseq(string& t) {
  return t == "+=";
}

bool Token::is_minus(string& t) {
  return t == "-";
}

bool Token::is_minusminus(string& t) {
  return t == "--";
}

bool Token::is_minuseq(string& t) {
  return t == "-=";
}

bool Token::is_mul(string& t) {
  return t == "*";
}

bool Token::is_muleq(string& t) {
  return t == "*=";
}

bool Token::is_div(string& t) {
  return t == "/";
}

bool Token::is_diveq(string& t) {
  return t == "/=";
}

bool Token::is_mod(string& t) {
  return t == "%";
}

bool Token::is_modeq(string& t) {
  return t == "%=";
}

bool Token::is_lt(string& t) {
  return t == "<";
}

bool Token::is_le(string& t) {
  return t == "<=";
}

bool Token::is_gt(string& t) {
  return t == ">";
}

bool Token::is_ge(string& t) {
  return t == ">=";
}

bool Token::is_eq(string& t) {
  return t == "==";
}

bool Token::is_ne(string& t) {
  return t == "!=";
}

bool Token::is_par_l(string& t) {
  return t == "(";
}

bool Token::is_par_r(string& t) {
  return t == ")";
}

bool Token::is_accol_l(string& t) {
  return t == "{";
}

bool Token::is_accol_r(string& t) {
  return t == "}";
}

bool Token::is_if(string& t) {
  return t == "if";
}

bool Token::is_else(string& t) {
  return t == "else";
}

bool Token::is_elseif(string& t) {
  return t == "elseif";
}

bool Token::is_while(string& t) {
  return t == "while";
}

bool Token::is_do(string& t) {
  return t == "do";
}

bool Token::is_for(string& t) {
  return t == "for";
}

bool Token::is_print_i(string& t) {
  return t == "print_i";
}

bool Token::is_print_s(string& t) {
  return t == "print_s";
}

bool Token::is_scan_i(string& t) {
  return t == "scan_i";
}

bool Token::is_scan_s(string& t) {
  return t == "scan_s";
}

bool Token::is_true(string& t) {
  return t == "true";
}

bool Token::is_false(string& t) {
  return t == "false";
}

bool Token::is_return(string& t) {
  return t == "return";
}
