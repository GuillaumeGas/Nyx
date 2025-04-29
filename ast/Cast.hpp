#pragma once

#include <iostream>
#include "Ast.hpp"
#include "../global/Position.hpp"
#include "Type.hpp"
#include "Object.hpp"
#include "Expression.hpp"

namespace nyx {
    namespace ast {
        typedef ExpressionPtr CastPtr;

        class DllExport Cast : public Expression {
        public:
            Cast(Type* type, ExpressionPtr expr, Position* pos);
            ~Cast();

            void print(std::ostream& out, int offset = 0) const;
            ExpressionPtr interpretExpression(bool returnSymValue = false);

            Type* getType() const;
            void setType(Type* type);
            ExpressionPtr getExpr() const;
            void setExpr(ExpressionPtr expr);

        private:
            Type* _type;
            ExpressionPtr _expr;
        };
    };
};
