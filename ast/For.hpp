#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Bloc.hpp"
#include "VarId.hpp"
#include "../global/Position.hpp"

namespace nyx {
    namespace ast {
        typedef InstructionPtr ForPtr;

        class DllExport For : public Instruction {
        public:
            For(std::string* ident, VarIdPtr varLoop, ExpressionPtr expr, BlocPtr bloc, Position* pos);
            ~For();

            void print(std::ostream& out, int offset = 0) const;
            void declare();
            void interpret();

            std::string* getIdent() const;
            void setIdent(std::string* ident);
            VarIdPtr getVarLoop() const;
            void setVarLoop(VarIdPtr varLoop);
            ExpressionPtr getExpr() const;
            void setExpr(ExpressionPtr expr);
            BlocPtr getBloc() const;
            void setBloc(BlocPtr bloc);

        private:
            std::string* _ident;
            VarIdPtr _varLoop;
            ExpressionPtr _expr;
            BlocPtr _bloc;
        };
    };
};
