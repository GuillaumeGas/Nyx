#pragma once

#include <iostream>
#include <vector>

#include "Ast.hpp"
#include "Declaration.hpp"
#include "../global/Position.hpp"
#include "VarDecl.hpp"

namespace nyx
{
    namespace ast
    {
        class StructDecl;
        typedef std::shared_ptr<StructDecl> StructPtr;
        typedef DeclarationPtr StructDeclPtr;

        class StructDecl : public Declaration,
            public std::enable_shared_from_this<StructDecl> {
        public:
            StructDecl(const std::string& name, Position* pos, std::vector<MemberPtr>* membersDecl);
            ~StructDecl();

            void declare() override;
            void interpret() override;
            void staticAnalysis() override;
            void print(std::ostream& out, int offset = 0) const;

            std::string getName() const;
            void setName(const std::string& name);

        private:
            std::string _name;
            std::vector<MemberPtr>* _members;
        };
    };
};