#pragma once

#include <iostream>
#include <iomanip>
#include "Operator.hpp"
#include "Expression.hpp"
#include "Object.hpp"
#include "../global/Position.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
        typedef ExpressionPtr BinopPtr;

        class Binop : public Expression {
        public:
            Binop(ExpressionPtr left, ExpressionPtr right, Operator* op, Position* pos);
            ~Binop();

            ExpressionPtr interpretExpression(bool returnSymValue = false);
            void declare();
            void interpret();
            void print(std::ostream& out, int offset = 0) const;

            ExpressionPtr getLeft() const;
            void setLeft(ExpressionPtr left);
            ExpressionPtr getRight() const;
            void setRight(ExpressionPtr right);
            Operator* getOp() const;
            void setOp(Operator* op);

        private:
            ExpressionPtr _left;
            ExpressionPtr _right;
            Operator* _op;
        };
    };
};
