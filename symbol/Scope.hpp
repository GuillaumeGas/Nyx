#pragma once

#include <iostream>
#include <map>
#include <sstream>

#include "Symbol.hpp"
#include "exceptions/SymbolException.hpp"
#include "../global/Global.hpp"
#include "../ast/Position.hpp"

/**
   Scope class : contains symbols, may have a parent and a child.
 */
namespace nyx {
    namespace symbol {
	class Scope {
	public:
	    Scope(Scope * parent = NULL);
	    ~Scope();

	    /**
	       Creates a new scope and returns it
	     */
	    Scope * newScope();

	    /**
	       Returns the parent's scope
	     */
	    Scope * getParent();

	    /**
	       Add the symbol in the current scope
	     */
	    void addSymbol(Symbol * s, ast::Position * pos);

	    /**
	       Return the symbol according a name
	       Return NULL if the symbol was not found
	     */
	    Symbol * getSymbol(std::string name, ast::Position * pos);

	    std::string toString() const;

	private:
	    std::map<std::string, Symbol*> _list;
	    Scope * _parent_scope;
	    Scope * _next_scope;
	};
    };
};
