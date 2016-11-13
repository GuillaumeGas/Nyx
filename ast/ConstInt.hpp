#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Value.hpp"

namespace nyx {
    namespace ast {
	class ConstInt : public Expression {
	public:
	    ConstInt(int value, Position * pos);
	    ~ConstInt();

	    void print (std::ostream & out, int offset = 0) const;
	    Expression * interpret_expr();

	    Expression * sum(Expression * expr);
	};
    };
};
