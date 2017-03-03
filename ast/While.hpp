#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Bloc.hpp"
#include "../global/Position.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace nyx {
    namespace ast {
	typedef InstructionPtr WhilePtr;

	class While : public Instruction {
	public:
	    While (std::string * ident, ExpressionPtr expr, BlocPtr bloc, Position * pos);
	    ~While ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    std::string * ident;
	    ExpressionPtr expr;
	    BlocPtr bloc;
	};
    };
};
