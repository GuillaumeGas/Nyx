#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Expression.hpp"
#include "../global/Position.hpp"
#include "Type.hpp"

namespace nyx {
    namespace ast {
        typedef ExpressionPtr BoolPtr;
        typedef ExpressionPtr IntPtr;
        typedef ExpressionPtr CharPtr;
        typedef ExpressionPtr FloatPtr;
        typedef ExpressionPtr ArrayPtr;
        typedef ExpressionPtr StringPtr;
        typedef ExpressionPtr RangePtr;

        class Bool : public Expression {
        public:
            Bool(bool value, Position* pos);
            ~Bool();

            bool getBool() const;
            void print(std::ostream& out, int offset = 0) const;

            ExpressionPtr clone();
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

            ExpressionPtr interpretUnaryMINUS();

        private:
            bool value;
        };

        class Int : public Expression {
        public:
            Int(int value, Position* pos);
            ~Int();

            int getInt() const;
            void setInt(int v);

            void print(std::ostream& out, int offset = 0) const;

            ExpressionPtr clone();
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

            ExpressionPtr interpretUnaryMINUS();

        private:
            int value;
        };

        class Char : public Expression {
        public:
            Char(char value, Position* pos);
            ~Char();

            char getChar() const;
            void print(std::ostream& out, int offset = 0) const;

            ExpressionPtr clone();
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

            ExpressionPtr interpretUnaryMINUS();

        private:
            char value;
        };

        class Float : public Expression {
        public:
            Float(float value, Position* pos);
            ~Float();

            float getFloat() const;
            void print(std::ostream& out, int offset = 0) const;

            ExpressionPtr clone();
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

            ExpressionPtr interpretUnaryMINUS();

        private:
            float value;
        };

        class Array : public Expression {
        public:
            Array(std::vector<ExpressionPtr>* array, Position* pos);
            ~Array();

            std::vector<ExpressionPtr>* getArray() const;
            void print(std::ostream& out, int offset = 0) const;

            void declare();

            ExpressionPtr clone();
            ExpressionPtr interpretExpression(bool);
            // ExpressionPtr interpretAND (ExpressionPtr e);
            // ExpressionPtr interpretOR (ExpressionPtr e);
            ExpressionPtr interpretPLUS(ExpressionPtr e);

        protected:
            Array(Position* pos);
            std::vector<ExpressionPtr>* array;
        };

        class String : public Array {
        public:
            String(std::string str, Position* pos);
            String(const String& str, Position* pos);

            void print(std::ostream& out, int offset = 0) const;
        };

        class Range : public Expression {
        public:
            Range(ExpressionPtr begin, ExpressionPtr end, Position* pos);
            ~Range();

            void declare();

            ExpressionPtr getRangeBegin() const;
            ExpressionPtr getRangeEnd() const;
            void print(std::ostream& out, int offset = 0) const;

            ExpressionPtr clone();
            ExpressionPtr interpretExpression(bool);

            ExpressionPtr begin;
            ExpressionPtr end;
        };
    };
};
