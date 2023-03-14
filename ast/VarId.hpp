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

            void print(std::ostream& out, int offset = 0) const;

            bool getBool() const;
            int getInt() const;
            char getChar() const;
            float getFloat() const;
            std::vector<ExpressionPtr>* getArray() const;
            ExpressionPtr getRangeBegin() const;
            ExpressionPtr getRangeEnd() const;
            // Object * getObject () const;

            void declare() override;

            ExpressionPtr clone() override;
            ExpressionPtr interpretExpression() override;
            ExpressionPtr interpretASSIGN(ExpressionPtr e) override;
            ExpressionPtr interpretLE(ExpressionPtr e) override;
            ExpressionPtr interpretGE(ExpressionPtr e) override;
            ExpressionPtr interpretNE(ExpressionPtr e) override;
            ExpressionPtr interpretLT(ExpressionPtr e) override;
            ExpressionPtr interpretGT(ExpressionPtr e) override;
            ExpressionPtr interpretEQ(ExpressionPtr e) override;
            ExpressionPtr interpretAND(ExpressionPtr e) override;
            ExpressionPtr interpretOR(ExpressionPtr e) override;
            ExpressionPtr interpretPLUS(ExpressionPtr e) override;
            ExpressionPtr interpretMINUS(ExpressionPtr e) override;
            ExpressionPtr interpretMUL(ExpressionPtr e) override;
            ExpressionPtr interpretDIV(ExpressionPtr e) override;
            ExpressionPtr interpretMOD(ExpressionPtr e) override;
            ExpressionPtr interpretPOINT(ExpressionPtr e) override;

            ExpressionPtr interpretUnaryMINUS() override;
        private:
            std::string _name;
            ExpressionPtr _value;

            ExpressionPtr _interpretBinop(Op op, ExpressionPtr e);
        };
    };
};
