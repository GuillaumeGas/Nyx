#pragma once

#include <iostream>
#include "Symbol.hpp"
#include "Scope.hpp"
#include "../ast/Position.hpp"

namespace nyx {
    namespace symbol {
	class Table {
	public:
	    static Table * getInstance();
	    ~Table();

	    void enterBlock();
	    void exitBlock();
	    void addSymbol(Symbol * s, ast::Position * pos);
	    Symbol * getSymbol(std::string name, ast::Position * pos);

	    std::string toString() const;

	private:
	    Table();

	    static Table * instance;

	    Scope main_scope;
	    Scope * current_scope;
	};
    };
};
