#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Bloc.hpp"
#include "VarId.hpp"
#include "ConstInt.hpp"
#include "Position.hpp"

namespace bob {
    namespace ast {
	class For : public Ast {
	public:
	    For (VarId * var_loop, ConstInt * start_value, ConstInt * end_value, Bloc * bloc, Position * pos);
	    ~For ();

	    void print (std::ostream & out, int offset = 0) const;
	    void interpret ();

	private:
	    VarId * var_loop;
	    ConstInt * start_value;
	    ConstInt * end_value;
	    Bloc * bloc;
	};
    };
};
