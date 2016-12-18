#pragma once

#include <iostream>

namespace nyx {
    namespace ast {
	class Position {
	public:
	    Position (unsigned int line, unsigned int column);
	    Position (const Position& p);
	    ~Position();
	    std::string toString() const;
	    unsigned int line;
	    unsigned int column;
	};
    };
};
