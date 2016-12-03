#include "Lexer.hpp"

using namespace std;

Lexer::Lexer (string file_name) {
    this->file_name = file_name;
    this->current_loc.line = 0;
    this->current_loc.column = 0;
    this->eof = false;
    this->current_index = 0;

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
	    return Token::make (it.second, {0, 0});
	}
    }
    return Token::makeEof ();
}

Token Lexer::getWord (int index) {
    if (index >= 0) {
	if (index == this->current_line.size()) {
	    this->current_line.push_back (getWord ());
	}
	return this->current_line[index];
    } else {
	throw -1;
    }
}

void Lexer::rewind () {
    if (this->current_index > 0)
	this->current_index--;
}

Token Lexer::next () {
    Token t = getWord (this->current_index++);
    Token com = isCom (t);
    while (isSkip (t) || !com.isEof ()) {
	if (!com.isEof ()) {
	    do {
		t = getWord (this->current_index++);
	    } while (t.value != com.value && !t.isEof ());
	    com = Token::makeEof ();
	    if (!t.isEof ())
		t = getWord (this->current_index++);
	} else {
	    t = getWord (this->current_index++);
	}
	com = isCom (t);
    }
    return t;
}

// Token Lexer::next () {
//     Token t = this->getWord ();
//     Token com = isCom (t);
//     while (isSkip (t) || !com.isEof ()) {
// 	if (!com.isEof ()) {
// 	    do {
// 		t = this->getWord ();
// 	    } while (t.value != com.value && !t.isEof());
// 	    com = Token::makeEof ();
// 	    if (!t.isEof())
// 		t = this->getWord ();
// 	} else {
// 	    t = this->getWord ();
// 	}
// 	com = isCom (t);
//     }
//     return t;
// }

Token Lexer::getWord () {
    int current_pos = ftell (this->file);
    string line;
    this->getLine (line);

    if (line.size() == 0) {
	this->eof = true;
	return Token::makeEof ();
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
	return Token::make (line, loc);
    } else if (pos == 0) {
	mfseek (tok, current_pos+tok.size());
	this->current_loc.column += tok.size();
	return Token::make (tok, loc);
    } else {
	string str = line.substr (0, pos);
	mfseek (str, current_pos+pos);
	this->current_loc.column += pos;
	return Token::make (str, loc);
    }
}

void Lexer::getLine (string & line) {
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
