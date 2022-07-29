#pragma once

#include <iostream>
#include <map>
#include <sstream>

#include "Symbol.hpp"
#include "exceptions/SymbolException.hpp"
#include "../global/Global.hpp"
#include "../global/Position.hpp"

/**
   Scope class : contains symbols, may have a parent and a child.
 */
namespace nyx {
	namespace symbol {
		class Scope {
		public:
			Scope(Scope* parent = NULL);
			~Scope();

			/**
			   Creates a new scope and returns it
			 */
			Scope* newScope();

			/**
			   Creates a new function scope and returns it
			 */
			Scope* newFunScope();

			/**
			   Returns the parent's scope
			 */
			Scope* getParent();

			/**
			   Add the symbol in the current scope
			 */
			void addSymbol(Symbol* s, Position* pos);

			/**
			   Add the Function symbole in the current scope
			 */
			void addFunSymbol(FunSymbol* s, Position* pos);

			/**
			   Return the symbol according a name
			   Return NULL if the symbol was not found
			 */
			virtual Symbol* getSymbol(std::string name, Position* pos);

			/**
			   Returns the function symbol according to a name
			   Returns NULL if the symbol was not found
			 */
			virtual FunSymbol* getFunSymbol(std::string name, Position* pos);

			std::string toString() const;

			void checkForUnusedSymbols();

		protected:
			std::map<std::string, Symbol*> _symbolsList;
			std::map<std::string, FunSymbol*> _funSymbolsList;
			Scope* _parent_scope;
			Scope* _next_scope;
		};

		class FunScope : public Scope {
		public:
			FunScope(Scope* parent);
			/**
			   Return the symbol according a name
			   Return NULL if the symbol was not found
			 */
			Symbol* getSymbol(std::string name, Position* pos);

			/**
			   Returns the function symbol according to a name
			   Returns NULL if the symbol was not found
			 */
			FunSymbol* getFunSymbol(std::string name, Position* pos);
		};
	};
};
