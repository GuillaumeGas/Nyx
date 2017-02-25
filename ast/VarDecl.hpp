#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Type.hpp"
#include "../global/Position.hpp"
#include "VarId.hpp"

namespace nyx {
    namespace ast {
	class VarDecl : public Ast {
	public:
	    VarDecl (VarId * var_id, Position * pos);
	    VarDecl (Type * type, VarId * var_id, Position * pos);
	    ~VarDecl();

	    void secondPass ();
	    void print (std::ostream & out, int offset = 0) const;

	    Type * type;
	    VarId * var_id;
	};
    };
};
