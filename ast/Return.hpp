#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"
#include "Object.hpp"
#include "Function.hpp"
#include "../global/Position.hpp"

namespace nyx {
    namespace ast {
        typedef InstructionPtr ReturnPtr;

        class Return : public Instruction {
        public:
            Return(ExpressionPtr expr, Position* pos);

            void print(std::ostream& out, int offset = 0) const;
            void interpret();

            ExpressionPtr getExpr() const;
            void setExpr(ExpressionPtr expr);

        private:
            ExpressionPtr _expr;
        };
    };
};
