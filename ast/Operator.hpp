#pragma once

#include <iostream>

#define DllExport __declspec(dllexport)

namespace nyx {
    namespace ast {
        enum Op {
            PLUSPLUS,
            MINUSMINUS,
            POINT,
            NOT,
            PLUS,
            MINUS,
            MUL,
            DIV,
            MOD,
            MULEQ,
            DIVEQ,
            PLUSEQ,
            MINUSEQ,
            MODEQ,
            ASSIGN,
            LT,
            LE,
            GT,
            GE,
            EQ,
            NE,
            AND,
            OR,
            INDEX,
            NEW,
            UNKNOWN
        };

        class DllExport Operator {
        public:
            Operator(std::string s);
            Operator(const Operator& op);
            Op value;

            std::string toString() const;
            static Op getValue(std::string s);

        private:
            std::string str;
        };

    };
};
