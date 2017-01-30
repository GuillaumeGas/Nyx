#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

#include "Ast.hpp"
#include "../symbol/Table.hpp"

namespace nyx {
    namespace ast {
	class Bloc : public Ast {
	public:
	    Bloc (std::vector<Ast*> * content);
	    Bloc (std::vector<Ast*> * content, bool is_global);
	    ~Bloc ();

	    void interpret();
	    void print (std::ostream & out, int offset = 0) const;

	    std::vector<Ast*> * content;
	private:
	    bool _is_global;
	};
    };
};
