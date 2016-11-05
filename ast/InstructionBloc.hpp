#pragma once

#include <iostream>
#include <deque>
#include "Ast.hpp"

namespace bob {
    namespace ast {
	class InstructionBloc : public Ast {
	public:
	    InstructionBloc (std::deque<Ast*> * instructions_list, Position * pos);

	    std::string to_string() const;
	    void interpret ();

	private:
	    std::deque<Ast*> * instructions_list;
	};
    };
};
