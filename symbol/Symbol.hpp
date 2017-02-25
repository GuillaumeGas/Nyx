
#pragma once

#include <iostream>
#include <sstream>
#include "../ast/Type.hpp"
#include "../ast/Object.hpp"
#include "../ast/FunDecl.hpp"

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

	    /**
	       Set the symbol's const state
	     */
	    void setConst (bool is_const);

	    std::string toString() const;

	protected:
	    std::string _name;
	    ast::AbstractObject * _ptr;
	    bool _is_def;
	    bool _is_const;
	};

	class ConstSymbol : public Symbol {
	public:
	    ConstSymbol (std::string & name, ast::AbstractObject * ptr);
	    ConstSymbol (std::string & name);
	};

	class FunSymbol {
	public:
	    FunSymbol (std::string & name, ast::FunDecl * ptr);
	    std::string getName () const;
	    ast::FunDecl * getPtr () const;

	    std::string toString () const;
	private:
	    ast::FunDecl * _ptr;
	    std::string _name;
	};
    };
};
