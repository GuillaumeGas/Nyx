#include "Lexer.cpp"

using namespace std;

Lexer::Lexer (string file_name) {
  this->file_name = file_name;
  this->current_line = "";
  this->current_pos = 0;
  this->current_loc.column = 0;
  this->current_loc.line = 0;

  this->file = new ifstream (file_name.c_str(), std::ios::in); 

  if (!this->file->is_open()) {
    cout << "Error file" << endl;
    exit (-1);
  }
}

Lexer::~Lexer () {
  if (this->file) {
    this->file->close ();
    delete this->file;
  }
}

//TODO : si on doit passer des commentaires, on les passe...
Token Lexer::next () { return this->getWord (); }

Token Lexer::getWord () {
  if (this->current_pos == this->current_line->size())
    getline (this->file, this->current_line);
  this->current_loc.line++;
  this->current_loc.column = 0;

  if (this->current_line.size() == 0)
    return TokenEof (current_loc);

  int max = 0, pos = -1;
  string tok = "";
  for (auto it : this->keys) {
    int index = this->current_line.find (it);
    if (index > 0) {
      if (index < first_pos) { 
	pos = index;
	max = it.size();
	tok = it;
      } else if (index == first_pos) {
	if (max < it.size()) {
	  max = it.size();
	  tok = it;
	}
      }
    }
  }

  if (pos == -1)
    return Token (this->current_line, this->current_loc);
  if (pos == this->current_loc.column) {
    location_t loc;
    loc.line = this->current_loc.line;
    loc.column = this->current_loc.column;
    this->current_loc.column += this->tok.size();
    return Token (this->tok, loc);
  }
  return Token (this->current_line.substr (this->current_loc.column, pos));
    
}

Token::Token (string value, location_t loc) {
  this->value = value;
  this->loc = loc;
}

TokenEof::TokenEof (location_t loc) : Token ("EOF", loc) {}
