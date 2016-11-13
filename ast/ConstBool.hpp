#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace nyx {
    namespace ast {
	class ConstBool : public Expression {
	public:
	    ConstBool(bool value, Position * pos);
	    ~ConstBool();

	    void print (std::ostream & out, int offset = 0) const;
	};
    };
};
