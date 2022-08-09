#pragma once

#include <iostream>

#define DEFAULT_LINE 1
#define DEFAULT_COLUMN 0

#define NULL_POSITION_PTR				\
    (Position *) NULL

namespace nyx {
    class Position {
    public:
        Position(unsigned int line, unsigned int column, std::string filePath);
        Position(const Position& p);
        Position();
        ~Position();
        std::string toString() const;
        unsigned int line;
        unsigned int column;
        std::string filePath;
    };

    class DefaultPosition : public Position {
    public:
        DefaultPosition();
    };
};
