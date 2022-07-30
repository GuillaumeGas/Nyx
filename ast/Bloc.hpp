#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>

#include "Ast.hpp"
#include "Instruction.hpp"

namespace nyx {
    namespace ast {
        class Bloc;
        typedef std::shared_ptr<Bloc> BlocPtr;

        class Bloc : public Instruction {
        public:
            Bloc(std::vector<InstructionPtr>* content);
            ~Bloc();

            void interpret();
            void print(std::ostream& out, int offset = 0) const;

            std::vector<InstructionPtr>* getContent() const;

            static BlocPtr New(std::vector<InstructionPtr>* content);

        private:
            std::vector<InstructionPtr>* _content;
        };
    };
};
