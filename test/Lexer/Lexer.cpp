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
    for (auto it : keys) {
	this->keys.push_back (it);
    }
}

//TODO : si on doit passer des commentaires, on les passe...
Token Lexer::next () { return this->get_word (); }

Token Lexer::get_word () {
    string line = this->read_line (this->current_index);

    // cout << "line : " << line << endl;

    if (line.size() == 0) {
	this->eof = true;
	return TokenEof (current_loc);
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

    // cout << "tok : [" << tok << "]" << endl;

    location_t loc;
    loc.line = this->current_loc.line;
    loc.column = this->current_loc.column;

    if (index == -1) {
	this->current_index += line.size();
	this->current_loc.column += line.size();
	return Token (line, loc);
    } else if (pos == 0) {
	this->current_loc.column += tok.size();
	this->current_index += tok.size();
	return Token (tok, loc);
    } else {
	int offset = (pos - this->current_loc.column);
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
    }
    file->seekg (0);
    return res;
}

Token::Token (string _value, location_t _loc) {
    value = _value;
    loc = _loc;
}

string Token::to_string() const {
    return "<" + value + ", loc(" + std::to_string(loc.line) + ", " + std::to_string(loc.column) + ")>";
}

TokenEof::TokenEof (location_t _loc) : Token ("EOF", _loc) {}
