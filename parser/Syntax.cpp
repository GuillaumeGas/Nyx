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

/**
   bloc := '{'? instruction* '}'?
*/
ast::Bloc * Syntax::visitBloc () {
    vector<ast::Ast*> * instr = new vector<ast::Ast*> ();
    Token * next = pop ();
    Token * begin = next;
    if (begin->type == TokenType::ACCOL_L)
	next = pop();
    while (next->type != TokenType::_EOF_ && next->type != TokenType::ACCOL_R) {
	switch (next->type) {
	case TokenType::TYPE:
	case TokenType::IDENT:
	case TokenType::SYSCALL:
	case TokenType::RETURN:
	case TokenType::BREAK:
	    instr->push_back (visitInstruction (next));
	    break;
	case TokenType::IF:
	    instr->push_back (visitIfElse (next));
	    break;
	case TokenType::FOR:
	    instr->push_back (visitFor (next));
	    break;
	case TokenType::WHILE:
	    instr->push_back (visitWhile (next));
	    break;
	default:
	    throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
	}
	next = pop ();
    }

    if (begin->type == TokenType::ACCOL_L && next->type != TokenType::ACCOL_R)
	throw MissingErrorException ("}", Position (next->line, next->column));

    return new ast::Bloc (instr);
}

/**
   instruction := (FunDecl | VarDecl | FunCall | VarAssign | Syscall);
*/
ast::Ast * Syntax::visitInstruction (Token * token) {
    ast::Ast * res = NULL;
    Token * next;
    if (token->type == TokenType::TYPE) {
	Token * type = token;
	next = pop ();
	if (next->type == TokenType::IDENT) {
	    Token * ident = next;
	    next = front ();
	    if (next->type == TokenType::PAR_L) {
		return visitFunDecl (type, ident);
	    } else if (next->type == TokenType::ASSIGN
		       || next->type == TokenType::SEMICOLON
		       || next->type == TokenType::COLON) {
		res = visitVarDecl (type, ident);
	    }
	} else {
	    throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
	}
    } else if (token->type == TokenType::IDENT) {
	Token * ident = token;
	next = front ();
	if (next->type == TokenType::PAR_L) {
	    res = visitFunCall (ident);
	} else if (next->type == TokenType::ASSIGN) {
	    res = visitVarAssign (ident);
	} else {
	    throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
	}
    } else if (token->type == TokenType::SYSCALL) {
	res = visitSyscall (token);
    } else if (token->type == TokenType::RETURN) {
	res = visitReturn (token);
    } else if (token->type == TokenType::BREAK) {
	res = visitBreak (token);
    } else {
	throw SyntaxErrorException (token->value->to_string(), Position (token->line, token->column));
    }
    next = pop();
    if (next->type != TokenType::SEMICOLON)
	throw MissingErrorException (";", Position (next->line, next->column));
    return res;
}

/**
   fundecl := type ident (params*) { bloc }
*/
ast::Ast * Syntax::visitFunDecl (Token * token_type, Token * token_ident) {
    pop();
    Token * next = front();
    vector <ast::VarDecl*> * params = NULL;
    if (next->type != TokenType::PAR_R) {
	params = visitParamsDecl ();
    } else {
	pop();
    }

    next = front();
    if (next->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position (next->line, next->column));

    ast::Bloc * content = visitBloc ();
    ast::Type * type = new ast::Type (token_type->value->to_string(), true);
    string ident = token_ident->value->to_string();
    ast::Position * pos = new ast::Position (token_type->line, token_type->column);

    return new ast::FunDecl (type, ident, params, content, pos);
}

/**
   params := (type ident*))
*/
vector <ast::VarDecl*> * Syntax::visitParamsDecl () {
    vector <ast::VarDecl*> * params = new vector <ast::VarDecl*> ();
    Token * next;
    do {
	Token * type = pop();
	Token * ident = pop();
	next = pop();

	if (type->type != TokenType::TYPE)
	    throw SyntaxErrorException (type->value->to_string(), Position (type->line, type->column));
	if (ident->type != TokenType::IDENT)
	    throw SyntaxErrorException (ident->value->to_string(), Position (ident->line, ident->column));
	if (next->type != TokenType::COLON && next->type != TokenType::PAR_R)
	    throw MissingErrorException (")", Position (next->line, next->column));

	ast::Type * ast_type = new ast::Type (type->value->to_string(), true);
	ast::Position * pos = new ast::Position (type->line, type->column);
	params->push_back (new ast::VarDecl (ast_type, ident->value->to_string(), pos));
    } while (next->type == TokenType::COLON);

    return params;
}

/**
   funcall := ident ( params* )
*/
ast::Ast * Syntax::visitFunCall (Token * token) {
    vector<ast::Expression*> * params = visitParams ();
    ast::Position * pos = new ast::Position (token->line, token->column);
    return new ast::FunCall (token->value->to_string(), params, pos);
}

/**
   varDecl := type (ident (= expression),)*;
*/
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


/**
   varAssign := ident = expression;
*/
ast::Ast * Syntax::visitVarAssign (Token * token_ident) {
    Token * token_op = pop();
    ast::Position * pos = new ast::Position (token_ident->line, token_ident->column);
    ast::Expression * e1 = new ast::VarId (token_ident->value->to_string(), pos);
    ast::Expression * e2 = visitExpression ();
    ast::Operator * op = new ast::Operator (token_op->value->to_string());

    return new ast::VarAssign (e1, e2, op, new ast::Position (token_op->line, token_op->column));
}

/**
   ifElse := if (expression) { bloc } (else (if (expression))? { bloc })*
*/
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
	ast::Bloc * bloc_else;
	if (next->type == TokenType::ACCOL_L) {
	    bloc_else = visitBloc ();
	} else if (next->type == TokenType::IF) {
	    bloc_else = (ast::Bloc*) visitIfElse (next);
	} else {
	    throw MissingErrorException ("{", Position (next->line, next->column));
	}
	return new ast::IfElse (expr_condition, bloc_if, bloc_else, pos);
    } else {
	return new ast::IfElse (expr_condition, bloc_if, pos);
    }

}

/**
   For := for (i in 0 .. 10)*/
ast::Ast * Syntax::visitFor (Token * token) {
    Token * next = pop();
    Token * ident = NULL;
    if (next->type == TokenType::COMMA) {
	next = pop();
	if (next->type != TokenType::IDENT)
	    throw MissingErrorException ("ident", Position (next->line, next->column));
	ident = next;
	next = pop();
    }
    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));

    next = pop();
    if (next->type != TokenType::IDENT)
	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));

    Token * var = next;
    next = pop();
    if (next->type != TokenType::IN)
	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));

    next = pop();
    if (next->type != TokenType::INT)
	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
    Token * start = next;
    if (pop()->type != TokenType::POINT)
	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
    next = pop();
    if (next->type != TokenType::INT)
	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
    Token * end = next;
    if (pop()->type != TokenType::PAR_R)
	throw MissingErrorException (")", Position(next->line, next->column));
    if (pop()->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position(next->line, next->column));

    ast::Bloc * for_bloc = visitBloc ();
    ast::VarId * var_loop = new ast::VarId (var->value->to_string(), new ast::Position (var->line, var->column));
    ast::ConstInt * start_value = (ast::ConstInt*)create_value (start);
    ast::ConstInt * end_value = (ast::ConstInt*)create_value (end);
    ast::Position * pos = new ast::Position (token->line, token->column);
    string * id = ident ? new string (ident->value->to_string()) : NULL;

    return new ast::For (id, var_loop, start_value, end_value, for_bloc, pos);
}

/**
   While := While ( expr ) { bloc }
*/
ast::Ast * Syntax::visitWhile (Token * token) {
    Token * ident = NULL;
    if (front()->type == TokenType::COMMA) {
	pop();
	ident = pop();
	if (ident->type != TokenType::IDENT)
	    throw MissingErrorException ("ident", Position (ident->line, ident->column));
    }
    ast::Expression * expr = visitExpression ();
    Token * next = pop();
    if (next->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position (next->line, next->column));

    ast::Bloc * bloc = visitBloc ();
    ast::Position * pos = new ast::Position (token->line, token->column);
    string * id = ident ? new string (ident->value->to_string()) : NULL;

    return new ast::While (id, expr, bloc, pos);
}

/**
   syscall := $ident ( params* );
*/
ast::Ast * Syntax::visitSyscall (Token * token) {
    vector<ast::Expression*> * params = visitParams ();
    ast::Position * pos = new ast::Position (token->line, token->column);
    return new ast::Syscall (token->value->to_string(), params, pos);
}


/**
   params := (varid*)
*/
vector<ast::Expression*> * Syntax::visitParams () {
    Token * next = pop();
    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));
    next = front();
    vector<ast::Expression*> * params = NULL;
    if (next->type != TokenType::PAR_R) {
	vector<char> delimitors;
	delimitors.push_back (',');
	delimitors.push_back (')');
	while (next->type != TokenType::PAR_R) {
	    if (next->type == TokenType::COLON) {
		if (!params) {
		    throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
		}
	    }

	    if (!params)
		params = new vector<ast::Expression*> ();

	    params->push_back (visitExpression (&delimitors));

	    next = pop();
	    if (next->type != TokenType::COLON && next->type != TokenType::PAR_R)
		throw MissingErrorException (")", Position (next->line, next->column));
	}
    }
    return params;
}

/**
   Return := return expression*;
*/
ast::Ast * Syntax::visitReturn (Token * token) {
    ast::Position * pos = new ast::Position (token->line, token->column);
    ast::Expression * expr = NULL;
    if (front()->type != TokenType::SEMICOLON)
	expr = visitExpression ();
    return new ast::Return (expr, pos);
}

/**
   Break := break ident?;
*/
ast::Ast * Syntax::visitBreak (Token * token) {
    ast::Position * pos = new ast::Position (token->line, token->column);
    string * ident = NULL;
    Token * next = front();
    if (next->type == TokenType::IDENT) {
	pop();
	ident = new string (next->value->to_string());
    }
    return new ast::Break (ident, pos);
}

ast::Expression * Syntax::visitExpression (vector<char> * delimitors) {
    /* Transformation de l'expression en notation polonaise inversée */
    queue<Token*> out;
    stack<Token*> op;

    Token * current_token = front();
    Token * tmp = NULL;
    int nb_par_l = 0;

    while (is_part_of_expr(current_token)) {
	string val = current_token->value->to_string();

	if (Token::is_value(current_token) || Token::is_ident(current_token)) {
	    out.push(current_token);
	} else if (Token::is_par_l(current_token)) {
	    nb_par_l++;
	    op.push(current_token);
	} else if (Token::is_par_r(current_token)) {
	    if (delimitors && is_delimitor (')', delimitors)) {
		if (nb_par_l == 0) {
		    break;
		}
	    }
	    nb_par_l--;
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

	pop();
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

bool Syntax::is_delimitor (char c, vector<char> * delimitors) {
    for (int i = 0; i < delimitors->size(); i++) {
	if ((*delimitors)[i] == c)
	    return true;
    }
    return false;
}
