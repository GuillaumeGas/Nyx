#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Position.hpp"
#include "FunDecl.hpp"
#include "Bloc.hpp"

namespace nyx {
    namespace ast {
	class Class : public Ast {
	public:
	    Class (std::string & ident, FunDecl * constructor, FunDecl * destructor, Bloc * public_bloc, Bloc * private_bloc, Position * pos);
	    Class (std::string & ident, std::string & inheritance, FunDecl * constructor, FunDecl * destructor, Bloc * public_bloc, Bloc * private_bloc, Position * pos);
	    ~Class ();

	    void interpret ();
	    void print (std::ostream & out, int offset = 0) const;

	private:
	    std::string ident;
	    std::string inheritance;
	    FunDecl * constructor;
	    FunDecl * destructor;
	    Bloc * public_bloc;
	    Bloc * private_bloc;
	};
    };
};
