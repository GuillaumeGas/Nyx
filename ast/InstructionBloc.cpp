#include "InstructionBloc.hpp"

using namespace std;
using namespace bob;
using namespace ast;

InstructionBloc::InstructionBloc (deque<Ast*> * instructions_list, Position * pos) {
    this->instructions_list = instructions_list;
    this->pos = pos;
}

void InstructionBloc::print (ostream & out, int offset) const {
    for (auto it = instructions_list->begin(); it != instructions_list->end(); it++) {
	(*it)->print (out, offset);
    }
}

void InstructionBloc::interpret() {
    for (auto it = instructions_list->begin(); it != instructions_list->end(); it++) {
	(*it)->interpret();
    }
}
