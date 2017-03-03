#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Instruction.hpp"
#include "../global/Position.hpp"

namespace nyx {
    namespace ast {
	typedef InstructionPtr ImportPtr;

	class Import : public Instruction {
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
