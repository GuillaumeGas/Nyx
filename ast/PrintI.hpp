#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace bob {
    namespace ast {
	class PrintI : public Ast {
	public:
	    PrintI(Expression * expr, Position * pos);
	    ~PrintI();

	    void interpret() const;
	    std::string to_string() const;

	    Expression * expr;
	};
    };
};
