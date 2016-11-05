#include "InstructionBloc.hpp"

using namespace std;
using namespace bob;
using namespace ast;

InstructionBloc::InstructionBloc (deque<Ast*> * instructions_list, Position * pos) {
    this->instructions_list = instructions_list;
    this->pos = pos;
}

string InstructionBloc::to_string() const {
    string res = "";
    for (auto it = instructions_list->begin(); it != instructions_list->end(); it++) {
	res += (*it)->to_string();
    }
    return res;
}

void InstructionBloc::interpret() {
    for (auto it = instructions_list->begin(); it != instructions_list->end(); it++) {
	(*it)->interpret();
    }
}
