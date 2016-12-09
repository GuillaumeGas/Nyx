#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Bloc.hpp"
#include "VarId.hpp"
#include "Position.hpp"

namespace nyx {
    namespace ast {
	class For : public Ast {
	public:
	    For (std::string * ident, VarId * var_loop, Expression * start_value, Expression * end_value, Bloc * bloc, Position * pos);
	    For (std::string * ident, VarId * var_loop, Expression * array, Bloc * bloc, Position * pos);
	    ~For ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    std::string  * ident;
	    VarId * var_loop;
	    Expression * start_value;
	    Expression * end_value;
	    Expression * array;
	    Bloc * bloc;
	};
    };
};
