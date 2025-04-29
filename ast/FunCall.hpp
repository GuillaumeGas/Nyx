#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "../global/Position.hpp"
#include "Expression.hpp"

namespace nyx {
    namespace ast {
        typedef InstructionPtr FunCallPtr;
        typedef ExpressionPtr ExprFunCallPtr;

        class DllExport FunCall : public Expression {
        public:
            FunCall(std::string name, std::vector<ExpressionPtr>* params, Position* pos);
            ~FunCall();

            void print(std::ostream& out, int offset = 0) const;

            void declare();
            void interpret();
            ExpressionPtr interpretExpression(bool returnSymValue = false);

        private:
            std::string _name;
            std::vector<ExpressionPtr>* _params;
        };
    };
};
