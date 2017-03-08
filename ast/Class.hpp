#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Declaration.hpp"
#include "../global/Position.hpp"
#include "Function.hpp"
#include "Bloc.hpp"

namespace nyx {
    namespace ast {
	typedef DeclarationPtr ClassPtr;

	class Class : public Declaration {
	public:
	    Class (std::string & ident, FunctionPtr constructor, FunctionPtr destructor, BlocPtr public_bloc, BlocPtr private_bloc, Position * pos);
	    Class (std::string & ident, std::string & inheritance, FunctionPtr constructor, FunctionPtr destructor, BlocPtr public_bloc, BlocPtr private_bloc, Position * pos);
	    ~Class ();

	    void interpret ();
	    void print (std::ostream & out, int offset = 0) const;
	private:
	    std::string ident;
	    std::string inheritance;
	    FunctionPtr constructor;
	    FunctionPtr destructor;
	    BlocPtr public_bloc;
	    BlocPtr private_bloc;
	};
    };
};
