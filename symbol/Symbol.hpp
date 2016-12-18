#pragma once

#include <iostream>
#include <sstream>
#include "../ast/Type.hpp"
#include "../ast/Value.hpp"

namespace nyx {
    namespace symbol {
	class Symbol {
	public:
	    Symbol (std::string & name, ast::Type * type);
	    Symbol (std::string & name, int value);
	    Symbol (std::string & name, float value);
	    Symbol (std::string & name, bool value);
	    Symbol (std::string & name, char value);
	    Symbol (std::string & name, std::string * value);
	    ~Symbol ();

	    void setValue (int value);
	    void setValue (float value);
	    void setValue (char value);
	    void setValue (bool value);
	    void setValue (std::string * value);

	    ast::Type * getType() const;
	    ast::Value * getValue () const;
	    std::string toString() const;

	    std::string name;
	    ast::Type * type;
	    ast::Value * value;
	};
    };
};
