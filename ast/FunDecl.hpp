#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "VarDecl.hpp"
#include "Bloc.hpp"

namespace bob {
    namespace ast {
	class FunDecl : public Ast {
	public:
	    FunDecl (Type * type, std::string ident, std::vector<VarDecl*> * params, Bloc * content, Position * pos);
	    ~FunDecl ();

	    void interpret ();
	    void print (std::ostream & out, int offset = 0) const;

	private:
	    Type * type;
	    std::string name;
	    std::vector<VarDecl*> * params;
	    Bloc * content;
	};
    };
};
