#pragma once

#include <iostream>
#include "Ast.hpp"

namespace nyx {
    namespace ast {
	class Instruction : public Ast {
	public:
	    virtual ~Instruction();
	    virtual void interpret ();
	    virtual void print (std::ostream & out, int offset = 0) const = 0;
	};
    };
};
