#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Value.hpp"

namespace bob {
    namespace ast {
	class ConstInt : public Expression {
	public:
	    ConstInt(int value, Position * pos);
	    ~ConstInt();

	    std::string to_string() const;
	    Expression * interpret_expr();

	    int get_int();
	    Expression * sum(Expression * expr);
	};
    };
};
