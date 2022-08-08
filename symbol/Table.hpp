#pragma once

#include <iostream>
#include <list>
#include <sstream>
#include <stack>

#include "Symbol.hpp"
#include "Scope.hpp"
#include "../global/Position.hpp"
#include "../ast/Object.hpp"
#include "../ast/Function.hpp"

#define MAIN_FUN_NAME "main"

/**
   Symbol table

   Keep a pointer on the global scope and the current scope.
 */
namespace nyx {
    namespace symbol {
        class Table {
        public:
            static Table* getInstance();
            ~Table();

            /**
               The current_scope pointer point on a new scope
             */
            void enterBlock();

            /**
               The current_scope pointer point on a new function scope (its behavior is different than a classic scope)
             */
            void enterFunBlock(ast::FunctionPtr fun);

            /**
               Quit the current block : call freeGarbage, destroy the current_scope and set it to its parent
             */
            void exitBlock();
            void exitFunBlock();

            /**
               Add a symbol in the current scope, raise an exception if the symbol already exist in the table
             */
            void addSymbol(Symbol* s, Position* pos);

            /**
               Add a function symbol in the current scope, raise an exception if the symbol already exist with the same parameters
             */
            void addFunSymbol(FunSymbol* s, Position* pos);

            /**
               Return a symbol depending on its name, raise an exception if the symbol is not found in the table
             */
            Symbol* getSymbol(std::string name, Position* pos) const;
            Symbol* getGlobalSymbol(std::string name, Position* pos) const;

            /**
               Returns a symbol depending on its name, raise an exception if the symbol is not found in the table
             */
            FunSymbol* getFunSymbol(std::string name, Position* pos) const;

            /**
               Returns a pointer on the current function in which we are
             */
            ast::FunctionPtr getCurrentFunction() const;

            /**
            * Returns a pointer on the current scope
            */
            Scope* getCurrentScope() const;

            std::string toString() const;

	    void dumpVariablesOfCurrentScope();

            void release();

        private:
            Table();

            static Table* instance;

            Scope* global_scope;
            Scope* current_scope;
            std::stack<ast::FunctionPtr> funcalls_stack;
        };
    };
};
