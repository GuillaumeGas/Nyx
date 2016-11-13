#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace nyx {
    namespace ast {
	class PrintI : public Ast {
	public:
	    PrintI(Expression * expr, Position * pos);
	    ~PrintI();

	    void interpret() const;
	    void print (std::ostream & out, int offset = 0) const;

	    Expression * expr;
	};
    };
};
