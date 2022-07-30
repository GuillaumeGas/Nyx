#include <sstream>

#include "Position.hpp"

using namespace std;
using namespace nyx;

Position::Position(unsigned int line, unsigned int column) : line(line), column(column) {}

Position::Position(const Position& p) : line(p.line), column(p.column) {}

Position::~Position() {  }

string Position::toString() const {
    stringstream ss;
    ss << "Line " << line << ", column " << column;
    return ss.str();
}

DefaultPosition::DefaultPosition() : Position(DEFAULT_LINE, DEFAULT_COLUMN) {}
