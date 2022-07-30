#pragma once

#include <iostream>
#include <vector>

#include "Ast.hpp"
#include "Declaration.hpp"
#include "Expression.hpp"
#include "Bloc.hpp"
#include "../global/Position.hpp"
#include "Type.hpp"
#include "VarDecl.hpp"
#include "Object.hpp"

namespace nyx {
    namespace ast {
        class Function;
        typedef std::shared_ptr<Function> FunctionPtr;
        typedef DeclarationPtr FunctionDeclPtr;

        class Function : public Declaration,
            public std::enable_shared_from_this<Function> {
        public:
            Function(const std::string& name, Position* pos, Type* type, std::vector<ParamPtr>* params, BlocPtr content);
            ~Function();

            void declare();
            void interpret();
            ExpressionPtr execute(std::vector<ExpressionPtr>* params);
            void print(std::ostream& out, int offset = 0) const;

            Type* getType() const;
            void setType(Type* type);
            std::string getName() const;
            void setName(const std::string& name);
            BlocPtr getContent() const;
            void setContent(BlocPtr content);
            ExpressionPtr getRet() const;
            void setRet(ExpressionPtr ret);

        private:
            std::string _name;
            Type* _type;
            std::vector<ParamPtr>* _params;
            BlocPtr _content;
            std::vector<ExpressionPtr> _ret;
        };
    };
};
