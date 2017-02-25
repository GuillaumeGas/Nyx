#pragma once

#include <iostream>
#include <list>
#include <sstream>

#include "Symbol.hpp"
#include "Scope.hpp"
#include "../global/Position.hpp"
#include "../ast/Object.hpp"

/**
   Symbol table

   Keep a pointer on the global scope and the current scope.
 */
namespace nyx {
    namespace symbol {
	class Table {
	public:
	    static Table * getInstance();
	    ~Table();

	    /**
	       The current_scope pointer point on a new scope
	     */
	    void enterBlock ();

	    /**
	       Quit the current block : call freeGarbage, destroy the current_scope and set it to its parent
	     */
	    void exitBlock ();

	    /**
	       Add a symbol in the current scope, raise an exception if the symbol already exist in the table
	     */
	    void addSymbol (Symbol * s, Position * pos);

	    /**
	       Return a symbol depending on its name, raise an exception if the symbol is not found in the table
	     */
	    Symbol * getSymbol (std::string name, Position * pos);

	    std::string toString() const;

	private:
	    Table();

	    static Table * instance;

	    Scope * global_scope;
	    Scope * current_scope;
	};
    };
};
