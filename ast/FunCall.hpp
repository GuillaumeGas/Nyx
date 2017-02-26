#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "../global/Position.hpp"
#include "Expression.hpp"

namespace nyx {
    namespace ast {
	class FunCall : public Expression {
	public:
	    FunCall (std::string ident, std::vector<Expression*> * params, Position * pos);
	    ~FunCall ();

	    void print (std::ostream & out, int offset = 0) const;

	    void interpret ();
	    AbstractObject * interpretExpression ();

	private:
	    std::string name;
	    std::vector<Expression*> * params;
	};
    };
};
