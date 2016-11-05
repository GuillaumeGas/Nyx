#include "Syntax.hpp"

#include "../symbol/Table.hpp"

using namespace std;
using namespace bob;
using namespace ast;

Syntax::Syntax(string& file_name, queue<Token*> * tokens) : m_file_name(file_name), m_tokens(tokens) {
    m_program = new Program();
    syntax::Program::visit(this);

    symbol::Table * t = symbol::Table::get_instance();
}

Syntax::~Syntax() {}

Token * Syntax::pop() const {
    Token * t = m_tokens->front();
    m_tokens->pop();
    return t;
}

Token * Syntax::front() const {
    return m_tokens->front();
}

void Syntax::add_elem(Ast * elem) {
    if (elem != NULL)
	m_program->content.push_back(elem);
}

Ast * Syntax::get_ast() const {
    return m_program;
}

bool Syntax::is_empty() const {
    return m_tokens->empty();
}
