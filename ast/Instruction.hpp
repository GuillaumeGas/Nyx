#pragma once

#include <iostream>
#include <memory>

#include "Ast.hpp"

namespace nyx {
    namespace ast {
	typedef AstPtr InstructionPtr;

	class Instruction : public Ast {
	public:
	    template <class T, class... Args>
	    static InstructionPtr New (Args&&... args) {
		return std::make_shared<T> (args...);
	    }
	};
    };
};
