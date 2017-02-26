#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Bloc.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"

namespace nyx {
    namespace ast {
	class IfElse : public Ast {
	public:
	    IfElse (Expression * cond, Bloc * bloc_if, Position * pos);
	    IfElse (Expression * cond, Bloc * bloc_id, Bloc * bloc_else, Position * pos);
	    ~IfElse ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    Expression * cond;
	    Bloc * bloc_if;
	    Bloc * bloc_else;
	};
    };
};
