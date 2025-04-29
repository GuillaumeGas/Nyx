#pragma once

#include <iostream>

#define DEFAULT_LINE 1
#define DEFAULT_COLUMN 0

#define NULL_POSITION_PTR				\
    (Position *) NULL

#define DllExport __declspec(dllexport)

namespace nyx {
    class DllExport Position {
    public:
        Position(unsigned int line, unsigned int column);
        Position(const Position& p);
        Position();
        ~Position();
        std::string toString() const;
        unsigned int line;
        unsigned int column;
    };

    class DefaultPosition : public Position {
    public:
        DefaultPosition();
    };
};
