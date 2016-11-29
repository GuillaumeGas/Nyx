#include "Lexer.hpp"

using namespace std;

Lexer::Lexer (string file_name) {
    this->file_name = file_name;
    this->current_loc.line = 0;
    this->current_loc.column = 0;
    this->eof = false;

    this->file = fopen (file_name.c_str (), "r");

    if (!this->file) {
	cout << "Error file" << endl;
	throw -1;
    }
}

Lexer::~Lexer () {
    if (this->file) {
	fclose (this->file);
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
	if (it.first == t.value) {
	    return Token (it.second, {0, 0});
	}
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
	com = isCom (t);
    }
    return t;
}

Token Lexer::get_word () {
    int current_pos = ftell (this->file);
    string line;
    this->get_line (line);

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
	mfseek (line, current_pos+line.size());
	this->current_loc.column += line.size();
	return Token (line, loc);
    } else if (pos == 0) {
	mfseek (tok, current_pos+tok.size());
	this->current_loc.column += tok.size();
	return Token (tok, loc);
    } else {
	string str = line.substr (0, pos);
	mfseek (str, current_pos+pos);
	this->current_loc.column += pos;
	return Token (str, loc);
    }
}

void Lexer::get_line (string & line) {
    unsigned int size = 256;
    while (1) {
	char * buffer = new char[size];
	fgets (buffer, size, this->file);
	if (!buffer) {
	    line = "";
	    break;
	}
	line += string (buffer);
	if (line.size() < size || line[line.size()-1] != '\n')
	    break;
	delete buffer;
    }
}

void Lexer::mfseek (const string & tok, unsigned int offset) {
    if (tok == "\n" || tok == "\r") {
	this->current_loc.line++;
	this->current_loc.column = 0;
    }
    fseek (this->file, offset, SEEK_SET);
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
