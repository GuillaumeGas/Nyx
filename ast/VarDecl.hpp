#pragma once

#include <iostream>
#include <iomanip>
#include "Ast.hpp"
#include "Instruction.hpp"
#include "Type.hpp"
#include "../global/Position.hpp"
#include "VarId.hpp"

namespace nyx {
    namespace ast {
        class VarDecl;
        typedef std::shared_ptr<VarDecl> ParamPtr;
        typedef std::shared_ptr<VarDecl> MemberPtr;
        typedef InstructionPtr VarDeclPtr;

        class DllExport VarDecl : public Instruction {
        public:
            VarDecl(VarIdPtr varId, Position* pos);
            VarDecl(Type* type, VarIdPtr varId, Position* pos);
            ~VarDecl();

            void declare();
            void interpret();
            void print(std::ostream& out, int offset = 0) const;

            Type* getType() const;
            void setType(Type* type);
            VarIdPtr getVarId() const;
            void setVarId(VarIdPtr varId);

            static ParamPtr New(Type* type, VarIdPtr varId, Position* pos);

        private:
            Type* _type;
            VarIdPtr _varId;
        };
    };
};
