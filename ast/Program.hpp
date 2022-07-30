#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Declaration.hpp"

namespace nyx {
    namespace ast {
        class Program {
        public:
            Program();
            ~Program();

            void execute();
            void print();

            void addDeclaration(DeclarationPtr declaration);

        private:
            std::vector<DeclarationPtr>* _content;

            void _declare();
        };
    };
};
