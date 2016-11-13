#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Position.hpp"
#include "Expression.hpp"

namespace nyx {
    namespace ast {
	class FunCall : public Ast {
	public:
	    FunCall (std::string ident, std::vector<Expression*> * params, Position * pos);
	    ~FunCall ();

	    void interpret ();
	    void print (std::ostream & out, int offset = 0) const;

	private:
	    std::string name;
	    std::vector<Expression*> * params;
	};
    };
};
