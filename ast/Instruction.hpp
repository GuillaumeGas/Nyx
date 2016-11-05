#pragma once

#include <iostream>
#include "Ast.hpp"

namespace bob {
    namespace ast {
	class Instruction : public Ast {
	public:
	    virtual ~Instruction();
	    virtual void interpret ();
	    virtual std::string to_string() const = 0;
	};
    };
};
