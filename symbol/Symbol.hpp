#pragma once

#include <iostream>
#include <sstream>
#include "../ast/Type.hpp"
#include "../ast/Object.hpp"

/**
   Symbol class : represents a symbol.

   It has a name and can have a value (an pointer on an AbstractObject)
   It can be defined or undefined (ex : let a; its type is undefined)
 */
namespace nyx {
    namespace symbol {
	class Symbol {
	public:
	    Symbol (std::string & name);
	    Symbol (std::string & name, ast::AbstractObject * ptr);
	    ~Symbol ();

	    /**
	       Returns the value, a pointer on an abstract object
	     */
	    ast::AbstractObject * getValue () const;

	    /**
	       Returns the symbol's name
	     */
	    std::string getName () const;

	    /**
	       Returns
	        - true if the symbol is defined
		- false if not (ex : let a; its type is undefined)
	     */
	    bool isDef () const;

	    /**
	       Set the symbol's value
	       The symbol becomes 'defined'
	     */
	    void setValue (ast::AbstractObject * v);

	    std::string toString() const;

	private:
	    std::string _name;
	    ast::AbstractObject * _ptr;
	    bool _is_def;
	};
    };
};
