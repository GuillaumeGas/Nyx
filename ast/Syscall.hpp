#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Instruction.hpp"
#include "Expression.hpp"
#include "../global/Position.hpp"
#include "exceptions/SemanticException.hpp"
#include "Object.hpp"

namespace nyx {
    namespace ast {
        typedef ExpressionPtr SyscallPtr;

        class DllExport Syscall : public Expression {
        public:
            Syscall(std::string ident, std::vector<ExpressionPtr>* params, Position* pos);
            ~Syscall();

            void print(std::ostream& out, int offset = 0) const;

            void declare();
            void interpret();
            ExpressionPtr interpretExpression(bool returnSymValue = false);

            //syscalls list
            ExpressionPtr sysPrint();
            ExpressionPtr sysPrintln();
            ExpressionPtr sysReadInt();
	        ExpressionPtr sysDebugBreak();

            std::string getIdent() const;
            void setIdent(const std::string& ident);
            std::vector<ExpressionPtr>* getParams() const;
            void setParams(std::vector<ExpressionPtr>* params);

        private:
            std::string _ident;
            std::vector<ExpressionPtr>* _params;

            void _sysPrint(ExpressionPtr e);
        };
    };
};
