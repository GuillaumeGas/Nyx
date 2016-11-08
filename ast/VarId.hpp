#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Value.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace bob {
    namespace ast {
	class VarId : public Expression {
	public:
	    VarId(std::string name, Position * pos);
	    ~VarId();

	    Expression * interpret_expr();
	    void print (std::ostream & out, int offset = 0) const;
	    Type * get_type() const;
	    Value * get_value() const;

	    std::string name;
	};
    };
};
