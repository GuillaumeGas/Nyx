#pragma once

#include <iostream>
#include "Ast.hpp"
#include "Instruction.hpp"
#include "../global/Position.hpp"

namespace nyx {
    namespace ast {
        typedef Instruction BreakPtr;

        class DllExport Break : public Instruction {
        public:
            Break(std::string* ident, Position* pos);
            ~Break();

            void interpret();
            void print(std::ostream& out, int offset = 0) const;

            std::string* getIdent() const;
            void setIdent(std::string* ident);

        private:
            std::string* _ident;
        };
    };
};
