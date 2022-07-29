
#pragma once

#include <iostream>
#include <sstream>
#include "../ast/Type.hpp"
#include "../ast/Object.hpp"
#include "../ast/Function.hpp"

/**
   Symbol class : represents a symbol.

   It has a name and can have a value (an pointer on an AbstractObject)
   It can be defined or undefined (ex : let a; its type is undefined)
 */
namespace nyx {
    namespace symbol {
	class Symbol {
	public:
	    Symbol (std::string name);
	    Symbol (std::string name, ast::ExpressionPtr ptr);
	    ~Symbol ();

	    /**
	       Returns the value, a pointer on an abstract object
	     */
	    ast::ExpressionPtr getValue ();

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
	    void setValue (ast::ExpressionPtr v);

	    /**
	       Set the symbol's const state
	     */
	    void setConst (bool is_const);

	    std::string toString() const;

		bool isUsed() const;

	protected:
	    std::string _name;
	    ast::ExpressionPtr _ptr;
	    bool _is_def;
	    bool _is_const;
		bool _used_at_least_once;
	};

	class ConstSymbol : public Symbol {
	public:
	    ConstSymbol (std::string name, ast::ExpressionPtr ptr);
	    ConstSymbol (std::string name);
	};

	class FunSymbol {
	public:
	    FunSymbol (std::string name, ast::FunctionPtr ptr);
	    std::string getName () const;
	    ast::FunctionPtr getPtr () const;

	    std::string toString () const;
	private:
	    ast::FunctionPtr _ptr;
	    std::string _name;
	};
    };
};
