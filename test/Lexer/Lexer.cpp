#include "Lexer.hpp"

using namespace std;

Lexer::Lexer (string file_name) {
  this->file_name = file_name;
  this->current_index = 0;
  this->current_loc.line = 0;
  this->current_loc.column = 0;
  this->eof = false;

  this->file = new ifstream (file_name.c_str(), std::ios::in);

  if (!this->file->is_open()) {
    cout << "Error file" << endl;
    throw -1;
  }
}

Lexer::~Lexer () {
  if (this->file) {
    this->file->close ();
    delete this->file;
  }
}

bool Lexer::isEof () const {
  return this->eof;
}

void Lexer::setKeys (vector<string> keys) {
  this->keys = keys;
}

void Lexer::setSkips (vector<string> skips) {
  this->skips = skips;
}

void Lexer::setComs (vector<pair<string, string> > coms) {
  this->coms = coms;
}

bool Lexer::isSkip (Token t) const {
  for (auto it : this->skips) {
    if (it == t.value)
      return true;
  }
  return false;
}

Token Lexer::isCom (Token t) const {
  for (auto it : this->coms) {
    if (it.first == t.value)
      return Token (it.second, {0, 0});
  }
  return TokenEof ();
}

Token Lexer::next () {
  Token t = this->get_word ();
  Token com = isCom (t);
  while (isSkip (t) || !com.isEof ()) {
    if (!com.isEof ()) {
      do {
  	t = this->get_word ();
      } while (t.value != com.value && !t.isEof());
      com = TokenEof ();
      if (!t.isEof())
	t = this->get_word ();
    } else {
      t = this->get_word ();
    }
  }
  return t;
}

Token Lexer::get_word () {
  string line = this->read_line (this->current_index);

  if (line.size() == 0) {
    this->eof = true;
    return TokenEof ();
  }

  int max = 0, pos = line.size(), index = -1;
  string tok = "";
  for (auto it : this->keys) {
    index = line.find (it);
    if (index > -1) {
      if (index < pos) {
	pos = index;
	max = it.size();
	tok = it;
      } else if (index == pos) {
	if (max < it.size()) {
	  max = it.size();
	  tok = it;
	}
      }
    }
  }

  location_t loc;
  loc.line = this->current_loc.line;
  loc.column = this->current_loc.column;

  if (pos == line.size()) {
    this->current_index += line.size();
    this->current_loc.column += line.size();
    return Token (line, loc);
  } else if (pos == 0) {
    this->current_loc.column += tok.size();
    this->current_index += tok.size();
    return Token (tok, loc);
  } else {
    this->current_index += pos;
    this->current_loc.column += pos;
    return Token (line.substr (0, pos), loc);
  }
}

string Lexer::read_line (unsigned int offset) {
  this->file->seekg (offset);
  string res = "";
  getline (*this->file, res);
  if (res.size() == 0) {
    getline (*this->file, res);
    this->current_index++;
    this->current_loc.line++;
    this->current_loc.column = 0;
    file->seekg (0);
    return res;
  }
}

Token::Token (string _value, location_t _loc) {
  value = _value;
  loc = _loc;
  eof = false;
}

string Token::to_string() const {
  return "<" + value + ", loc(" + std::to_string(loc.line) + ", " + std::to_string(loc.column) + ")>";
}

bool Token::isEof() const {
  return this->eof;
}

TokenEof::TokenEof () : Token ("EOF", {0, 0}) {
  this->eof = true;
}
