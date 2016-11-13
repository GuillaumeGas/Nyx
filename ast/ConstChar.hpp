#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace nyx {
    namespace ast {
	class ConstChar : public Expression {
	public:
	    ConstChar(const char value, Position * pos);
	    ~ConstChar();
	    void print (std::ostream & out, int offset = 0) const;
	};
    };
};
