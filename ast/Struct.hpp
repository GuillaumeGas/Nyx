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
        class Struct;
        typedef std::shared_ptr<Struct> StructPtr;
        typedef DeclarationPtr StructDeclPtr;

        class Struct : public Declaration,
            public std::enable_shared_from_this<Struct> {
        public:
            Struct(const std::string& name, Position* pos, std::vector<MemberPtr>* membersDecl);
            ~Struct();

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