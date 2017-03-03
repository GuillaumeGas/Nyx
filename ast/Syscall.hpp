#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Instruction.hpp"
#include "Expression.hpp"
#include "../global/Position.hpp"
#include "exceptions/SemanticException.hpp"
#include "Object.hpp"

namespace nyx {
    namespace ast {
	typedef Instruction SyscallPtr;

	class Syscall : public Instruction {
	public:
	    Syscall (std::string ident, std::vector<ExpressionPtr> * params, Position * pos);
	    ~Syscall ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	    //syscalls list
	    void sysPrint ();
	    void sysPrintln ();

	private:
	    std::string ident;
	    std::vector<ExpressionPtr> * params;

	    void _sysPrint (ExpressionPtr e);
	};
    };
};
