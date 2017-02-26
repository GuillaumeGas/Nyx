#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "../global/Position.hpp"
#include "Type.hpp"
#include "VarDecl.hpp"

namespace nyx {
    namespace ast {
	class Bloc;

	class FunDecl : public Ast {
	public:
	    FunDecl (Type * type, const std::string & ident, std::vector<VarDecl*> * params, Bloc * content, Position * pos);
	    ~FunDecl ();

	    void registerFunctions ();
	    void execute (std::vector<Expression*> * params);

	    void print (std::ostream & out, int offset = 0) const;

	private:
	    Type * type;
	    std::string name;
	    std::vector<VarDecl*> * params;
	    Bloc * content;
	};
    };
};
