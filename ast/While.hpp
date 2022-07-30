#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Bloc.hpp"
#include "../global/Position.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
        typedef InstructionPtr WhilePtr;

        class While : public Instruction {
        public:
            While(std::string* ident, ExpressionPtr expr, BlocPtr bloc, Position* pos);
            ~While();

            void print(std::ostream& out, int offset = 0) const;
            void interpret();

            std::string* getIdent() const;
            void setIdent(const std::string* ident);
            ExpressionPtr getExpr() const;
            void setExpr(ExpressionPtr expr);
            BlocPtr getBloc() const;
            void setBloc(BlocPtr bloc);

        private:
            std::string* _ident;
            ExpressionPtr _expr;
            BlocPtr _bloc;
        };
    };
};
