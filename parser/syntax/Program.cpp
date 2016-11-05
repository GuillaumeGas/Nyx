#include "Program.hpp"

using namespace bob;
using namespace syntax;
using namespace std;

void Program::visit(Syntax * syntax) {
    while (!syntax->is_empty()) {
	ast::InstructionBloc * bloc = InstructionBloc::visit(syntax);
	syntax->add_elem (bloc);
    }
}
