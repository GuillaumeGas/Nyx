#pragma once

#include <iostream>
#include <vector>

#include "Ast.hpp"

namespace bob {
    namespace ast {
	class Bloc : public Ast {
	public:
	    Bloc(std::vector<Ast*> * content);
	    ~Bloc();

	    void interpret();
	    std::string to_string() const;

	    std::vector<Ast*> * content;
	};
    };
};
