#pragma once

#include <iostream>
#include <memory>

#include "Ast.hpp"

namespace nyx {
    namespace ast {
        struct Instruction;
        typedef std::shared_ptr<Instruction> InstructionPtr;

        struct DllExport Instruction : public Ast {
            Instruction(Position* pos);

            virtual void declare();
            virtual void interpret() = 0;

            template <class T, class... Args>
            static InstructionPtr New(Args&&... args) {
                return std::make_shared<T>(args...);
            }
        };
    };
};
