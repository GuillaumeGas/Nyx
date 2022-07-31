#pragma once

#include <vector>

#include "Symbol.hpp"

namespace nyx {
    namespace symbol {
        class StaticAnalysis {
        public:
            static StaticAnalysis* getInstance();
            ~StaticAnalysis();

            void addUnusedSymbol(std::string name, Position pos);
            void displayUnusedSymbols() const;

        private:
            StaticAnalysis();

            static StaticAnalysis* _instance;

            std::vector<std::pair<std::string, Position>> _unusedSymbols;
        };
    }
}