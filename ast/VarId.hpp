#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Const.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Value.hpp"
#include "exceptions/SemanticException.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace nyx {
    namespace ast {
	class VarId : public Expression {
	public:
	    VarId(std::string name, Position * pos);
	    ~VarId();

	    void print (std::ostream & out, int offset = 0) const;

	    Expression * interpretExpression ();
	    Expression * interpretPlus (Expression * e);
	    Expression * interpretMinus (Expression * e) {}
	    Expression * interpretMul (Expression * e) {}
	    Expression * interpretDiv (Expression * e) {}
	    Expression * interpretMod (Expression * e) {}
	    Expression * interpretAssign (Expression * e) {}

	    Type * getType () const;
	    Value * getValue () const;

	    std::string name;
	};
    };
};
