#pragma once

#include <iostream>
#include <memory>

#include "../global/Position.hpp"

#define TODO_SEM(p)					\
    printf ("[!] TODO Semantic : %s\n", p);	\
    exit (-1);

#define INDENT 2

namespace nyx {
    namespace ast {
        class Ast {
        public:
            Ast(Position* pos);
            virtual ~Ast();
            virtual void print(std::ostream& out, int offset = 0) const = 0;
            virtual void interpret() = 0;

            template<class A, class B>
            static std::shared_ptr<A> PointerCast(B sharedPtr) {
                return std::static_pointer_cast<A> (sharedPtr);
            }

            Position* getPos() const;
            void setPos(Position* pos);

        protected:
            void shift(std::ostream& out, int offset) const;

            Position* _pos;
        };
    };
};
