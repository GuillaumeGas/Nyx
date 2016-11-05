#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "InstructionBloc.hpp"

namespace bob {
    namespace ast {
	class IfElse : public Ast {
	public:
	    IfElse (Expression * cond, InstructionBloc * bloc_if, Position * pos);
	    IfElse (Expression * cond, InstructionBloc * bloc_id, InstructionBloc * bloc_else, Position * pos);

	    std::string to_string() const;
	    void interpret ();

	private:
	    Expression * cond;
	    InstructionBloc * bloc_if;
	    InstructionBloc * bloc_else;
	};
    };
};
