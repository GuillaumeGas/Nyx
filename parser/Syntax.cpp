#include "Syntax.hpp"

using namespace std;
using namespace bob;
using namespace syntax;

Syntax::Syntax(string& file_name, queue<Token*> * tokens) : m_file_name(file_name), m_tokens(tokens) {
    m_table = symbol::Table::get_instance();
    m_program = visitBloc ();
}

Syntax::~Syntax() {}

Token * Syntax::pop() const {
    Token * t = m_tokens->front();
    m_tokens->pop();
    if (t)
	return t;
    return new TokenEof ();
}

Token * Syntax::front() const {
    Token * t = m_tokens->front();
    if (t)
	return t;
    return new TokenEof ();
}

bool Syntax::is_empty() const {
    return m_tokens->empty();
}

ast::Ast * Syntax::get_ast () const { return m_program; }

ast::Bloc * Syntax::visitBloc () {
    vector<ast::Ast*> * instr = new vector<ast::Ast*> ();
    Token * next = pop ();
    while (next->type != TokenType::_EOF_ && next->type != TokenType::ACCOL_R) {
	switch (next->type) {
	case TokenType::TYPE:
	case TokenType::IDENT:
	    instr->push_back (visitInstruction (next));
	    break;
	case TokenType::IF:
	    instr->push_back (visitIfElse (next));
	    break;
	default:
	    throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
	}
	next = pop ();
    }
    return new ast::Bloc (instr);
}

ast::Ast * Syntax::visitInstruction (Token * token) {
    ast::Ast * res = NULL;
    if (token->type == TokenType::TYPE) {
	Token * type = token;
	Token * next = pop ();
	if (next->type == TokenType::IDENT) {
	    Token * ident = next;
	    next = front ();
	    if (next->type == TokenType::PAR_L) {
		res = visitFunDecl (type, ident);
	    } else if (next->type == TokenType::ASSIGN
		       || next->type == TokenType::SEMICOLON
		       || next->type == TokenType::COLON) {
		res = visitVarDecl (type, ident);
	    } else {
		throw MissingErrorException (";", Position (next->line, next->column));
	    }
	    pop();
	} else {
	    throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
	}
    } else {
	throw SyntaxErrorException (token->value->to_string(), Position (token->line, token->column));
    }
    return res;
}

ast::Ast * Syntax::visitFunDecl (Token * token_type, Token * token_ident) {
    pop(); // '('
    TODO("FunDecl");
    return NULL;
}

ast::Bloc * Syntax::visitVarDecl (Token * token_type, Token * token_ident) {
    ast::Position * pos = new ast::Position (token_type->line, token_type->column);
    ast::Type * type = new ast::Type (token_type->value->to_string(), true);
    ast::VarDecl * var_decl = new ast::VarDecl (type, token_ident->value->to_string(), pos);

    vector<ast::Ast*> * instr = new vector<ast::Ast*> ();
    instr->push_back (var_decl);

    Token * next = front ();
    if (next->type == TokenType::ASSIGN) {
	instr->push_back (visitVarAssign (token_ident));
	next = front ();
    }
    if (next->type == TokenType::COLON) {
	pop();
	Token * ident = pop ();
	if (ident->type != TokenType::IDENT) {
	    throw SyntaxErrorException (ident->value->to_string(), Position (ident->line, ident->column));
	}
	instr->push_back (visitVarDecl (token_type, ident));
    }
    return new ast::Bloc (instr);
}

ast::Ast * Syntax::visitVarAssign (Token * token_ident) {
    Token * token_op = pop();
    ast::Position * pos = new ast::Position (token_ident->line, token_ident->column);
    ast::Expression * e1 = new ast::VarId (token_ident->value->to_string(), pos);
    ast::Expression * e2 = visitExpression ();
    ast::Operator * op = new ast::Operator (token_op->value->to_string());

    return new ast::VarAssign (e1, e2, op, new ast::Position (token_op->line, token_op->column));
}

ast::Ast * Syntax::visitIfElse (Token * token_if) {
    ast::Expression * expr_condition = Syntax::visitExpression ();
    ast::Position * pos = new ast::Position (token_if->line, token_if->column);

    Token * next = pop();
    if (next->type != ACCOL_L) {
	throw MissingErrorException ("{", Position (next->line, next->column));
    }

    ast::Bloc * bloc_if = visitBloc ();

    next = front();
    if (next->type == TokenType::ELSE) {
	pop();
	next = pop();
	if (next->type != ACCOL_L) {
	    throw MissingErrorException ("{", Position (next->line, next->column));
	}
	ast::Bloc * bloc_else = visitBloc ();
	return new ast::IfElse (expr_condition, bloc_if, bloc_else, pos);
    } else {
	return new ast::IfElse (expr_condition, bloc_if, pos);
    }

}

ast::Expression * Syntax::visitExpression () {
    /* Transformation de l'expression en notation polonaise inversée */
    queue<Token*> out;
    stack<Token*> op;

    Token * current_token = front();
    Token * tmp = NULL;

    while (is_part_of_expr(current_token)) {
	pop();
	string val = current_token->value->to_string();

	if (Token::is_value(current_token) || Token::is_ident(current_token)) {
	    out.push(current_token);
	} else if (Token::is_par_l(current_token)) {
	    op.push(current_token);
	} else if (Token::is_par_r(current_token)) {
	    tmp = op.top();
	    while (!Token::is_par_l(tmp) && op.size() > 0) {
		out.push(tmp);
		op.pop();
		if (op.size() > 0)
		    tmp = op.top();
	    }
	    if (!Token::is_par_l(tmp)) {
		throw SyntaxErrorException(tmp->value->to_string(), Position(tmp->line, tmp->column));
	    } else {
		op.pop();
	    }
	} else if (Token::is_binop(current_token)) {
	    if (op.size() == 0 || Token::is_par_l(op.top())) {
		op.push(current_token);
	    } else {
		ast::Operator op1(current_token->value->to_string());
		ast::Operator op2(op.top()->value->to_string());
		if (op1.priority > op2.priority) {
		    op.push(current_token);
		} else {
		    out.push(op.top());
		    op.pop();
		    op.push(current_token);
		}
	    }
	} else {
	    throw SyntaxErrorException(current_token->value->to_string(), Position(current_token->line, current_token->column));
	}

	Token * last = current_token;
	current_token = front();

	if (current_token == NULL)
	    throw MissingErrorException(";", Position(last->line, last->column));
    }
    while (op.size() > 0) {
	out.push(op.top());
	op.pop();
    }

    /* On prendl la sortie et créé l'ast relatif à l'expression */
    stack<ast::Expression*> st;

    while (out.size() > 0) {
	Token * t = out.front();
	out.pop();
	if (Token::is_value(t)) {
	    st.push(Syntax::create_value(t));
	} else if (Token::is_ident(t)) {
	    st.push(new ast::VarId(t->value->to_string(), new ast::Position(t->line, t->column)));
	} else {
	    ast::Operator * op = new ast::Operator(t->value->to_string());
	    ast::Expression * e2 = st.top();
	    st.pop();
	    ast::Expression * e1 = st.top();
	    st.pop();
	    st.push(new ast::Binop(e1, e2, op, new ast::Position(t->line, t->column)));
	}
    }
    if (st.size() != 1)
	throw MissingErrorException("operator", Position(st.top()->pos->line, st.top()->pos->column));

    return st.top();
}

ast::Expression * Syntax::create_value(Token * token) {
    ast::Position * pos = new ast::Position(token->line, token->column);
    TokenValue * token_value = token->value;
    switch (token->type) {
    case TokenType::INT:
	return new ast::ConstInt(((TokenIntValue*)token_value)->value, pos);
	break;
    case TokenType::CHAR:
	return new ast::ConstChar(((TokenCharValue*)token_value)->value, pos);
	break;
    case TokenType::BOOL:
	return new ast::ConstBool(((TokenBoolValue*)token_value)->value, pos);
	break;
    default:
	cout << "tok " << token->to_string() << endl;
	throw SyntaxErrorException(token->value->to_string(), Position(token->line, token->column));
    }
    return NULL;
}

bool Syntax::is_part_of_expr (Token * token) const {
    return token->type >= 0 && token->type <= 20;
}
