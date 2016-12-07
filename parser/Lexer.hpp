#pragma once

#include <iostream>
#include <cstdio>
#include <vector>

#include "../global/Global.hpp"
#include "Token.hpp"
#include "exceptions/LexerException.hpp"

namespace nyx {
    class Lexer {
    public:
	Lexer (std::string file_name);
	~Lexer ();

	void setKeys (std::vector<std::string> keys);
	void setSkips (std::vector<std::string> skips);
	void setComs (std::vector<std::pair<std::string, std::string> > coms);
	TokenPtr next ();
	bool isEof () const;
	void rewind (int count = 1);

    private:
	bool isSkip (TokenPtr t) const;
	TokenPtr isCom (TokenPtr t) const;
	TokenPtr getWord ();
	TokenPtr getWord (int index);
	void getLine (std::string & line);
	void mfseek (const std::string & tok, unsigned int offset);

	std::string file_name;
	FILE * file;
	location_t current_loc;
	int current_index;
	std::vector<TokenPtr> current_line;
	bool eof;
	bool new_line;
	std::vector<std::string> keys;
	std::vector<std::string> skips;
	std::vector<std::pair<std::string, std::string> > coms;
    };
};
