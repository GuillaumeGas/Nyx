#pragma once

#include <iostream>

#include "Position.hpp"

#define INDENT 5

namespace nyx {
    namespace ast {
	class Ast {
	public:
	    virtual ~Ast();
	    virtual void print(std::ostream & out, int offset = 0) const;
	    virtual void interpret();
	    Position * pos;

	protected:
	    void shift (std::ostream & out, int offset) const;
	};
    };
};
