#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Expression.hpp"

namespace nyx {
    namespace ast {
	class Cast : public Expression {
	public:
	    Cast (Type * type, Expression * expr, Position * pos);
	    ~Cast ();

	    void print (std::ostream & out, int offset = 0) const;



	private:
	    Type * type;
	    Expression * expr;
	};
    };
};
