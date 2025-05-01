#pragma once

#include <iostream>

#include "Expression.hpp"
#include "../global/Position.hpp"
#include "Object.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
        typedef ExpressionPtr IndexPtr;

        class DllExport Index : public Expression {
        public:
            Index(ExpressionPtr e1, ExpressionPtr e2, Position* pos);

            void print(std::ostream& out, int offset = 0) const;

            void declare();
            ExpressionPtr interpretExpression(bool returnSymValue = false);
            ExpressionPtr interpretASSIGN(ExpressionPtr e);
            ExpressionPtr interpretLE(ExpressionPtr e);
            ExpressionPtr interpretGE(ExpressionPtr e);
            ExpressionPtr interpretNE(ExpressionPtr e);
            ExpressionPtr interpretPLUSEQ(ExpressionPtr e);
            ExpressionPtr interpretMINUSEQ(ExpressionPtr e);
            ExpressionPtr interpretMULEQ(ExpressionPtr e);
            ExpressionPtr interpretDIVEQ(ExpressionPtr e);
            ExpressionPtr interpretMODEQ(ExpressionPtr e);
            ExpressionPtr interpretLT(ExpressionPtr e);
            ExpressionPtr interpretGT(ExpressionPtr e);
            ExpressionPtr interpretEQ(ExpressionPtr e);
            ExpressionPtr interpretAND(ExpressionPtr e);
            ExpressionPtr interpretOR(ExpressionPtr e);
            ExpressionPtr interpretPLUS(ExpressionPtr e);
            ExpressionPtr interpretMINUS(ExpressionPtr e);
            ExpressionPtr interpretMUL(ExpressionPtr e);
            ExpressionPtr interpretDIV(ExpressionPtr e);
            ExpressionPtr interpretMOD(ExpressionPtr e);
            ExpressionPtr interpretPOINT(ExpressionPtr e);

            ExpressionPtr e1;
            ExpressionPtr e2;

            ExpressionPtr res;

        private:
            bool _interpreted;
        };
    };
};
