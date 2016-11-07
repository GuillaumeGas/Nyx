#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Bloc.hpp"

namespace bob {
    namespace ast {
	class IfElse : public Ast {
	public:
	    IfElse (Expression * cond, Bloc * bloc_if, Position * pos);
	    IfElse (Expression * cond, Bloc * bloc_id, Bloc * bloc_else, Position * pos);

	    std::string to_string() const;
	    void interpret ();

	private:
	    Expression * cond;
	    Bloc * bloc_if;
	    Bloc * bloc_else;
	};
    };
};
