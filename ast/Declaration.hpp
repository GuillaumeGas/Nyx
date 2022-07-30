#pragma once

#include <iostream>
#include <memory>

#include "Ast.hpp"

namespace nyx {
    namespace ast {
        struct Declaration;
        typedef std::shared_ptr<Declaration> DeclarationPtr;

        struct Declaration : public Ast {
            Declaration(Position* pos);

            virtual void declare();
            virtual void interpret() = 0;
            virtual void staticAnalysis();

            template<class T, class... Args>
            static DeclarationPtr New(Args&&... args) {
                return std::shared_ptr<Declaration>(new T(args...));
            }
        };
    };
};
