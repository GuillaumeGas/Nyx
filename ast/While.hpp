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
	class While : public Ast {
	public:
	    While (std::string * ident, Expression * expr, Bloc * bloc, Position * pos);
	    ~While ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    std::string * ident;
	    Expression * expr;
	    Bloc * bloc;
	};
    };
};
