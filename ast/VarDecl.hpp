#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Type.hpp"
#include "Position.hpp"
#include "VarId.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace nyx {
    namespace ast {
	class VarDecl : public Ast {
	public:
	    VarDecl(Type * type, VarId * var_id, Position * pos);
	    ~VarDecl();

	    void interpret();
	    void print (std::ostream & out, int offset = 0) const;

	    Type * type;
	    VarId * var_id;
	};
    };
};
