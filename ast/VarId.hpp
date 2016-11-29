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

namespace nyx {
    namespace ast {
	class VarId : public Expression {
	public:
	    VarId(std::string name, Position * pos);
	    ~VarId();

	    Expression * interpretExpr();
	    void print (std::ostream & out, int offset = 0) const;
	    Type * getType() const;
	    Value * getValue() const;

	    std::string name;
	};
    };
};
