#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Bloc.hpp"
#include "Position.hpp"

namespace bob {
    namespace ast {
	class While : public Ast {
	public:
	    While (Expression * expr, Bloc * bloc, Position * pos);
	    ~While ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    Expression * expr;
	    Bloc * bloc;
	};
    };
};
