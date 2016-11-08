#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

#include "Ast.hpp"

namespace bob {
    namespace ast {
	class Bloc : public Ast {
	public:
	    Bloc(std::vector<Ast*> * content);
	    ~Bloc();

	    void interpret();
	    void print (std::ostream & out, int offset = 0) const;

	    std::vector<Ast*> * content;
	};
    };
};
