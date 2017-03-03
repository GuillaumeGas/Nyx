#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Instruction.hpp"
#include "../global/Position.hpp"

namespace nyx {
    namespace ast {
	typedef Instruction BreakPtr;

	class Break : public Instruction {
	public:
	    Break (std::string * ident, Position * pos);
	    ~Break ();

	    void secondPass ();
	    void print (std::ostream & out, int offset = 0) const;

	private:
	    std::string * ident;
	};
    };
};
