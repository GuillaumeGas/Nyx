#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Position.hpp"

namespace nyx {
    namespace ast {
	class Import : public Ast {
	public:
	    Import (std::vector<std::string> * path, Position * pos);
	    ~Import ();

	    void interpret ();
	    void print (std::ostream & out, int offset = 0) const;

	private:
	    std::vector<std::string> * path;
	};
    };
};
