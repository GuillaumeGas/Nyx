#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"

namespace bob {
    namespace ast {
	class Syscall : public Ast {
	public:
	    Syscall (std::string ident, std::vector<Expression*> * params, Position * pos);
	    ~Syscall ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    std::string ident;
	    std::vector<Expression*> * params;
	};
    };
};
