#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Bloc.hpp"
#include "VarId.hpp"
#include "../global/Position.hpp"

namespace nyx {
    namespace ast {
	class For : public Ast {
	public:
	    For (std::string * ident, VarId * var_loop, Expression * expr, Bloc * bloc, Position * pos);
	    ~For ();

	    void print (std::ostream & out, int offset = 0) const;
	    void secondPass ();

	private:
	    std::string  * ident;
	    VarId * var_loop;
	    Expression * expr;
	    Bloc * bloc;
	};
    };
};
