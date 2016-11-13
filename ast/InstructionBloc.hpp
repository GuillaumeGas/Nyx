#pragma once

#include <iostream>
#include <iomanip>
#include <deque>
#include "Ast.hpp"

namespace nyx {
    namespace ast {
	class InstructionBloc : public Ast {
	public:
	    InstructionBloc (std::deque<Ast*> * instructions_list, Position * pos);

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    std::deque<Ast*> * instructions_list;
	};
    };
};
