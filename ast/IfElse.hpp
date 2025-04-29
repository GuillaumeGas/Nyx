#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Bloc.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
        typedef InstructionPtr IfElsePtr;

        class DllExport IfElse : public Instruction {
        public:
            IfElse(ExpressionPtr cond, BlocPtr blocIf, Position* pos);
            IfElse(ExpressionPtr cond, BlocPtr blocIf, BlocPtr blocElse, Position* pos);
            IfElse(ExpressionPtr cond, BlocPtr blocIf, InstructionPtr elseIf, Position* pos);

            void print(std::ostream& out, int offset = 0) const;
            void declare();
            void interpret();

            ExpressionPtr getCond() const;
            void setCond(ExpressionPtr cond);
            BlocPtr getBlocIf() const;
            void setBlocIf(BlocPtr blocIf);
            BlocPtr getBlocElse() const;
            void setBlocElse(BlocPtr blocElse);
            InstructionPtr getElseIf() const;
            void setElseIf(InstructionPtr elseIf);

        private:
            ExpressionPtr _cond;
            BlocPtr _blocIf;
            BlocPtr _blocElse;
            InstructionPtr _blocElseIf;
        };
    };
};
