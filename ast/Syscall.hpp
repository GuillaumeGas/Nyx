#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Position.hpp"
#include "exceptions/SemanticException.hpp"
#include "Const.hpp"

namespace nyx {
    namespace ast {
	class Syscall : public Ast {
	public:
	    Syscall (std::string ident, std::vector<Expression*> * params, Position * pos);
	    ~Syscall ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	    //syscalls list
	    void sysPrint ();
	    void sysPrintln ();

	private:
	    std::string ident;
	    std::vector<Expression*> * params;

	    void _sysPrint (Expression * e);
	};
    };
};
