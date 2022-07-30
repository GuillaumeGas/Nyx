#pragma once

#include <vector>

namespace nyx {
    namespace symbol {
        class StaticAnalysis {
        public:
            static StaticAnalysis* getInstance();
            ~StaticAnalysis();

            void addUnusedSymbol(std::string symbolName);
            void displayUnusedSymbols() const;

        private:
            StaticAnalysis();

            static StaticAnalysis* _instance;

            std::vector<std::string> _unusedSymbols;
        };
    }
}