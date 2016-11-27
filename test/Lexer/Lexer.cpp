#include "Lexer.hpp"

using namespace std;

Lexer::Lexer (string file_name) {
    this->file_name = file_name;
    this->current_index = 0;
    this->current_loc.line = 1;
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
    for (auto it : keys) {
	this->keys.push_back (it);
    }
}

//TODO : si on doit passer des commentaires, on les passe...
Token Lexer::next () { return this->get_word (); }

Token Lexer::get_word () {
    string line = this->read_line (this->current_index);

    if (line.size() == 0)
	return TokenEof (current_loc);

    int max = 0, pos = line.size();
    string tok = "";
    for (auto it : this->keys) {
	int index = line.find (it);

	if (index > 0) {
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
    if (pos == -1) {
	Token t = Token (line, this->current_loc);
	this->current_index += line.size();
	return t;
    } else if (pos == current_pos) {
	loc.column = current_pos;
	this->current_index += tok.size();
	return Token (tok, loc);
    } else {
	Token t = Token (line.substr (this->current_loc.column, pos), this->current_loc);
	this->current_loc.column += (pos - this->current_loc.column);
    }
}

string Lexer::read_line (unsigned int offset) {
    this->file->seekg (offset);
    string res = "";
    getline (*this->file, res);
    if (res.size() == 0) {
	getline (*this->file, res);
	this->current_index++;
	loc.line++;
	loc.column = 0;
    }
    file->seekg (0);
    return res;
}

Token::Token (string _value, location_t _loc) {
    value = _value;
    loc = _loc;
}

string Token::to_string() const {
    return "<" + value + ", loc(" + std::to_string(loc.line) + ", " + std::to_string(loc.column) + ">";
}

TokenEof::TokenEof (location_t _loc) : Token ("EOF", _loc) {}
