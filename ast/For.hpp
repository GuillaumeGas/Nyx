#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Bloc.hpp"
#include "VarId.hpp"
#include "../global/Position.hpp"

namespace nyx {
    namespace ast {
	typedef InstructionPtr ForPtr;

	class For : public Instruction {
	public:
	    For (std::string * ident, VarIdPtr var_loop, ExpressionPtr expr, BlocPtr bloc, Position * pos);
	    ~For ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    std::string  * ident;
	    VarIdPtr var_loop;
	    ExpressionPtr expr;
	    BlocPtr bloc;
	};
    };
};
