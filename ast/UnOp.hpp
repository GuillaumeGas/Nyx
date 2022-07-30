#pragma once

#include <iostream>
#include <memory>
#include "Operator.hpp"
#include "Object.hpp"
#include "../global/Position.hpp"
#include "exceptions/SemanticException.hpp"
#include "Expression.hpp"

namespace nyx {
    namespace ast {
        typedef ExpressionPtr UnOpPtr;

        class UnOp : public Expression {
        public:
            UnOp(Operator* op, ExpressionPtr expr, Position* pos);
            ~UnOp();

            void print(std::ostream& out, int offset = 0) const;

            ExpressionPtr interpretExpression();

            Operator* getOp() const;
            void setOp(Operator* op);
            ExpressionPtr getExpr() const;
            void setExpr(ExpressionPtr expr);

        private:
            Operator* _op;
            ExpressionPtr _expr;
        };
    };
};
