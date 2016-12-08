#pragma once

#include <iostream>
#include <vector>

#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace nyx {
    namespace ast {
	struct Array : public Expression {
	    Array (std::vector<Expression*> * array, Position * pos);
	    ~Array ();

	    void print (std::ostream & out, int offset = 0) const;

	    std::vector<Expression*> * array;
	};
    };
};
