#pragma once

#include <iostream>
#include <vector>
#include "Ast.hpp"
#include "Declaration.hpp"
#include "../global/Position.hpp"

namespace nyx {
    namespace ast {
        typedef DeclarationPtr ImportPtr;

        class DllExport Import : public Declaration {
        public:
            Import(std::vector<std::string>* path, Position* pos);
            ~Import();

            void interpret();
            void print(std::ostream& out, int offset = 0) const;

        private:
            std::vector<std::string>* path;
        };
    };
};
