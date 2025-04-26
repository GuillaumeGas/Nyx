#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Ast.hpp"
#include "Expression.hpp"
#include "../global/Position.hpp"
#include "Type.hpp"
#include "Object.hpp"
#include "Operator.hpp"
#include "exceptions/SemanticException.hpp"

namespace nyx {
    namespace ast {
        class VarId;
        typedef std::shared_ptr<VarId> VarIdPtr;

        class VarId : public Expression {
        public:
            VarId(std::string name, Position* pos);
            VarId(std::string name, Position* pos, ExpressionPtr ptr);

            static VarIdPtr New(std::string name, Position* pos);
            static VarIdPtr New(std::string name, Position* pos, ExpressionPtr ptr);

            std::string getName() const;
            void setName(const std::string name);
            ExpressionPtr getValue() const;
            void setValue(ExpressionPtr value);

            void setIsStructMember(bool value);

            void print(std::ostream& out, int offset = 0) const;

            bool getBool() const;
            int getInt() const;
            char getChar() const;
            float getFloat() const;
            std::vector<ExpressionPtr>* getArray() const;
            ExpressionPtr getRangeBegin() const;
            ExpressionPtr getRangeEnd() const;
            // Object * getObject () const;

            void declare();

            ExpressionPtr clone();
            ExpressionPtr interpretExpression(bool returnSymValue = false);
            ExpressionPtr interpretASSIGN(ExpressionPtr e);
            ExpressionPtr interpretLE(ExpressionPtr e);
            ExpressionPtr interpretGE(ExpressionPtr e);
            ExpressionPtr interpretNE(ExpressionPtr e);
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

            ExpressionPtr interpretUnaryMINUS();

        private:
            std::string _name;
            ExpressionPtr _value;
            bool _isStructMember;

            ExpressionPtr _interpretBinop(Op op, ExpressionPtr e);
        };
    };
};
