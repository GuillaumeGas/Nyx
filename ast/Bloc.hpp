#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

#include "Ast.hpp"
#include "Instruction.hpp"
#include "../symbol/Table.hpp"

namespace nyx {
    namespace ast {
	typedef AstPtr BlocPtr;

	class Bloc : public Ast {
	public:
	    Bloc (std::vector<InstructionPtr> * content);
	    Bloc (std::vector<InstructionPtr> * content, bool is_global);
	    ~Bloc ();

	    void interpret ();
	    void print (std::ostream & out, int offset = 0) const;

	    std::vector<InstructionPtr> * content;
	private:
	    bool _is_global;
	};
    };
};
