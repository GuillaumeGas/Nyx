#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Bloc.hpp"
#include "VarId.hpp"
#include "ConstInt.hpp"
#include "Position.hpp"

namespace nyx {
    namespace ast {
	class For : public Ast {
	public:
	    For (std::string * ident, VarId * var_loop, ConstInt * start_value, ConstInt * end_value, Bloc * bloc, Position * pos);
	    ~For ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    std::string  * ident;
	    VarId * var_loop;
	    ConstInt * start_value;
	    ConstInt * end_value;
	    Bloc * bloc;
	};
    };
};