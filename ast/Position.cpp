#include "Position.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Position::Position(unsigned int line, unsigned int column) : line(line), column(column) {}
Position::Position(const Position& p) : line(p.line), column(p.column) {}
Position::~Position() {  }
string Position::to_string() const {
  return "Line " + std::to_string(line) + ", column " + std::to_string(column);
}
