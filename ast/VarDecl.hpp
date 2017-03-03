#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Instruction.hpp"
#include "Type.hpp"
#include "../global/Position.hpp"
#include "VarId.hpp"

namespace nyx {
    namespace ast {
	typedef InstructionPtr VarDeclPtr;

	class VarDecl : public Instruction {
	public:
	    VarDecl (VarIdPtr var_id, Position * pos);
	    VarDecl (Type * type, VarIdPtr var_id, Position * pos);
	    ~VarDecl();

	    void interpret ();
	    void print (std::ostream & out, int offset = 0) const;

	    Type * type;
	    VarIdPtr var_id;
	};
    };
};
