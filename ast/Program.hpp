#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Declaration.hpp"
#include "Expression.hpp"

namespace nyx {
    namespace ast {
        class DllExport Program {
        public:
            Program();
            ~Program();

            void staticAnalysis();
            void execute();
            void print(std::ostream & ostream);

            int getMainResult() const;

            void addDeclaration(DeclarationPtr declaration);

            std::vector<DeclarationPtr> getDeclarations();

        private:
            std::vector<DeclarationPtr>* _content;
            int _mainResult;

            void _declare();
        };
    };
};
