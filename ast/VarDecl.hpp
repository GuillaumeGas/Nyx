#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Type.hpp"
#include "Position.hpp"
#include "../symbol/Table.hpp"
#include "../symbol/Symbol.hpp"

namespace bob {
    namespace ast {
	class VarDecl : public Ast {
	public:
	    VarDecl(Type * type, std::string name, Position * pos);
	    ~VarDecl();

	    void interpret();
	    void print (std::ostream & out, int offset = 0) const;

	    Type * type;
	    std::string name;
	};
    };
};
