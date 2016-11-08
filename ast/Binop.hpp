#pragma once

#include <iostream>
#include <iomanip>
#include "Operator.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace bob {
    namespace ast {
	struct Binop : public Expression {
	    Binop(Expression * e1, Expression * e2, Operator * op, Position * pos);
	    ~Binop();

	    bool check_compatibility() const;
	    Expression * interpret_expr();
	    Expression * interpret_plus();
	    Expression * interpret_minus();
	    Expression * interpret_mul();
	    Expression * interpret_div();
	    Expression * interpret_mod();
	    Expression * interpret_assign();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * e1;
	    Expression * e2;
	    Operator * op;
	};
    };
};
