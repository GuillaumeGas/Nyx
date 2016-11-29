#include "Syntax.hpp"

using namespace std;
using namespace nyx;
using namespace syntax;

Syntax::Syntax(Lexer & lex) : lex(lex) {
    m_table = symbol::Table::getInstance();
    m_program = visitBloc ();
}

Syntax::~Syntax() {}

TokenPtr Syntax::pop() const {
    return lex.next ();
}

ast::Ast * Syntax::getAst () const { return m_program; }

/**
   bloc := '{'? instruction* '}'?
*/
ast::Bloc * Syntax::visitBloc () {
    vector<ast::Ast*> * instr = new vector<ast::Ast*> ();
    TokenPtr next = pop ();
    TokenPtr begin = next;
    if (begin->type == TokenType::ACCOL_L)
	next = pop();
    while (next->type != TokenType::_EOF_ && next->type != TokenType::ACCOL_R) {
	switch (next->type) {
	case TokenType::OTHER:
	case TokenType::DOLLAR:
	case TokenType::RETURN:
	case TokenType::BREAK:
	    instr->push_back (visitInstruction (next));
	    break;
	// case TokenType::IF:
	//     instr->push_back (visitIfElse (next));
	//     break;
	// case TokenType::FOR:
	//     instr->push_back (visitFor (next));
	//     break;
	// case TokenType::WHILE:
	//     instr->push_back (visitWhile (next));
	//     break;
	default:
	    throw SyntaxErrorException (next->value, Position (next->line, next->column));
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
ast::Ast * Syntax::visitInstruction (TokenPtr token) {
    ast::Ast * res = NULL;
    TokenPtr next;
    if (token->type == TokenType::OTHER) {
	TokenPtr type = token;
	next = pop ();
	if (next->type == TokenType::OTHER) {
	    TokenPtr ident = next;
	    next = pop ();
	    if (next->type == TokenType::PAR_L) {
		return NULL;
		// return visitFunDecl (type, ident);
	    } else if (next->type == TokenType::ASSIGN
		       || next->type == TokenType::SEMICOLON
		       || next->type == TokenType::COMMA) {
		res = visitVarDecl (type, ident, next);
	    }
	} else {
	    throw SyntaxErrorException (next->value, Position (next->line, next->column));
	}
    // } else if (token->type == TokenType::IDENT) {
    // 	TokenPtr ident = token;
    // 	next = front ();
    // 	if (next->type == TokenType::PAR_L) {
    // 	    res = visitFunCall (ident);
    // 	} else if (next->type == TokenType::ASSIGN) {
    // 	    res = visitVarAssign (ident);
    // 	} else {
    // 	    throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
    // 	}
    // } else if (token->type == TokenType::SYSCALL) {
    // 	res = visitSyscall (token);
    // } else if (token->type == TokenType::RETURN) {
    // 	res = visitReturn (token);
    // } else if (token->type == TokenType::BREAK) {
    // 	res = visitBreak (token);
    } else {
	throw SyntaxErrorException (token->value, Position (token->line, token->column));
    }
    if (next->type != TokenType::SEMICOLON)
	throw MissingErrorException (";", Position (next->line, next->column));
    return res;
}

/**
   fundecl := type ident (params*) { bloc }
*/
// ast::Ast * Syntax::visitFunDecl (TokenPtr token_type, TokenPtr token_ident) {
//     pop();
//     TokenPtr next = front();
//     vector <ast::VarDecl*> * params = NULL;
//     if (next->type != TokenType::PAR_R) {
// 	params = visitParamsDecl ();
//     } else {
// 	pop();
//     }

//     next = front();
//     if (next->type != TokenType::ACCOL_L)
// 	throw MissingErrorException ("{", Position (next->line, next->column));

//     ast::Bloc * content = visitBloc ();
//     ast::Type * type = new ast::Type (token_type->value->to_string(), true);
//     string ident = token_ident->value->to_string();
//     ast::Position * pos = new ast::Position (token_type->line, token_type->column);

//     return new ast::FunDecl (type, ident, params, content, pos);
// }

/**
   params := (type ident*))
*/
// vector <ast::VarDecl*> * Syntax::visitParamsDecl () {
//     vector <ast::VarDecl*> * params = new vector <ast::VarDecl*> ();
//     TokenPtr next;
//     do {
// 	TokenPtr type = pop();
// 	TokenPtr ident = pop();
// 	next = pop();

// 	if (type->type != TokenType::TYPE)
// 	    throw SyntaxErrorException (type->value->to_string(), Position (type->line, type->column));
// 	if (ident->type != TokenType::IDENT)
// 	    throw SyntaxErrorException (ident->value->to_string(), Position (ident->line, ident->column));
// 	if (next->type != TokenType::COMMA && next->type != TokenType::PAR_R)
// 	    throw MissingErrorException (")", Position (next->line, next->column));

// 	ast::Type * ast_type = new ast::Type (type->value->to_string(), true);
// 	ast::Position * pos = new ast::Position (type->line, type->column);
// 	params->push_back (new ast::VarDecl (ast_type, ident->value->to_string(), pos));
//     } while (next->type == TokenType::COMMA);

//     return params;
// }

/**
   funcall := ident ( params* )
*/
// ast::Ast * Syntax::visitFunCall (TokenPtr token) {
//     vector<ast::Expression*> * params = visitParams ();
//     ast::Position * pos = new ast::Position (token->line, token->column);
//     return new ast::FunCall (token->value->to_string(), params, pos);
// }

/**
   varDecl := type (ident (= expression),)*;
*/
ast::Bloc * Syntax::visitVarDecl (TokenPtr token_type, TokenPtr token_ident, TokenPtr next) {
    ast::Position * pos = new ast::Position (token_type->line, token_type->column);
    ast::Type * type = new ast::Type (token_type->value, true);
    ast::VarDecl * var_decl = new ast::VarDecl (type, token_ident->value, pos);

    vector<ast::Ast*> * instr = new vector<ast::Ast*> ();
    instr->push_back (var_decl);

    if (next->type == TokenType::ASSIGN) {
	// instr->push_back (visitVarAssign (token_ident, next));
	instr->push_back (NULL);
	next = pop ();
    }
    if (next->type == TokenType::COMMA) {
	TokenPtr ident = pop ();
	if (ident->type != TokenType::OTHER) {
	    throw SyntaxErrorException (ident->value, Position (ident->line, ident->column));
	}
	instr->push_back (visitVarDecl (token_type, ident, next));
    }
    return new ast::Bloc (instr);
}


/**
   varAssign := ident = expression;
*/
// ast::Ast * Syntax::visitVarAssign (TokenPtr token_ident, TokenPtr token_op) {
//     ast::Position * pos = new ast::Position (token_ident->line, token_ident->column);
//     ast::Expression * e1 = new ast::VarId (token_ident->value, pos);
//     ast::Expression * e2 = visitExpression ();
//     ast::Operator * op = new ast::Operator (token_op->value);

//     return new ast::VarAssign (e1, e2, op, new ast::Position (token_op->line, token_op->column));
// }

/**
   ifElse := if (expression) { bloc } (else (if (expression))? { bloc })*
*/
// ast::Ast * Syntax::visitIfElse (TokenPtr token_if) {
//     ast::Expression * expr_condition = Syntax::visitExpression ();
//     ast::Position * pos = new ast::Position (token_if->line, token_if->column);

//     TokenPtr next = pop();
//     if (next->type != ACCOL_L) {
// 	throw MissingErrorException ("{", Position (next->line, next->column));
//     }

//     ast::Bloc * bloc_if = visitBloc ();

//     next = front();
//     if (next->type == TokenType::ELSE) {
// 	pop();
// 	next = pop();
// 	ast::Bloc * bloc_else;
// 	if (next->type == TokenType::ACCOL_L) {
// 	    bloc_else = visitBloc ();
// 	} else if (next->type == TokenType::IF) {
// 	    bloc_else = (ast::Bloc*) visitIfElse (next);
// 	} else {
// 	    throw MissingErrorException ("{", Position (next->line, next->column));
// 	}
// 	return new ast::IfElse (expr_condition, bloc_if, bloc_else, pos);
//     } else {
// 	return new ast::IfElse (expr_condition, bloc_if, pos);
//     }

// }

/**
   For := for (i in 0 .. 10)*/
// ast::Ast * Syntax::visitFor (TokenPtr token) {
//     TokenPtr next = pop();
//     TokenPtr ident = NULL;
//     if (next->type == TokenType::COLON) {
// 	next = pop();
// 	if (next->type != TokenType::IDENT)
// 	    throw MissingErrorException ("ident", Position (next->line, next->column));
// 	ident = next;
// 	next = pop();
//     }
//     if (next->type != TokenType::PAR_L)
// 	throw MissingErrorException ("(", Position (next->line, next->column));

//     next = pop();
//     if (next->type != TokenType::IDENT)
// 	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));

//     TokenPtr var = next;
//     next = pop();
//     if (next->type != TokenType::IN)
// 	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));

//     next = pop();
//     if (next->type != TokenType::INT)
// 	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
//     TokenPtr start = next;
//     if (pop()->type != TokenType::POINT)
// 	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
//     next = pop();
//     if (next->type != TokenType::INT)
// 	throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
//     TokenPtr end = next;
//     if (pop()->type != TokenType::PAR_R)
// 	throw MissingErrorException (")", Position(next->line, next->column));
//     if (pop()->type != TokenType::ACCOL_L)
// 	throw MissingErrorException ("{", Position(next->line, next->column));

//     ast::Bloc * for_bloc = visitBloc ();
//     ast::VarId * var_loop = new ast::VarId (var->value->to_string(), new ast::Position (var->line, var->column));
//     ast::ConstInt * start_value = (ast::ConstInt*)create_value (start);
//     ast::ConstInt * end_value = (ast::ConstInt*)create_value (end);
//     ast::Position * pos = new ast::Position (token->line, token->column);
//     string * id = ident ? new string (ident->value->to_string()) : NULL;

//     return new ast::For (id, var_loop, start_value, end_value, for_bloc, pos);
// }

/**
   While := While ( expr ) { bloc }
*/
// ast::Ast * Syntax::visitWhile (TokenPtr token) {
//     TokenPtr ident = NULL;
//     if (front()->type == TokenType::COLON) {
// 	pop();
// 	ident = pop();
// 	if (ident->type != TokenType::IDENT)
// 	    throw MissingErrorException ("ident", Position (ident->line, ident->column));
//     }
//     ast::Expression * expr = visitExpression ();
//     TokenPtr next = pop();
//     if (next->type != TokenType::ACCOL_L)
// 	throw MissingErrorException ("{", Position (next->line, next->column));

//     ast::Bloc * bloc = visitBloc ();
//     ast::Position * pos = new ast::Position (token->line, token->column);
//     string * id = ident ? new string (ident->value->to_string()) : NULL;

//     return new ast::While (id, expr, bloc, pos);
// }

/**
   syscall := $ident ( params* );
*/
// ast::Ast * Syntax::visitSyscall (TokenPtr token) {
//     vector<ast::Expression*> * params = visitParams ();
//     ast::Position * pos = new ast::Position (token->line, token->column);
//     return new ast::Syscall (token->value->to_string(), params, pos);
// }


/**
   params := (varid*)
*/
// vector<ast::Expression*> * Syntax::visitParams () {
//     TokenPtr next = pop();
//     if (next->type != TokenType::PAR_L)
// 	throw MissingErrorException ("(", Position (next->line, next->column));
//     next = front();
//     vector<ast::Expression*> * params = NULL;
//     if (next->type != TokenType::PAR_R) {
// 	vector<char> delimitors;
// 	delimitors.push_back (',');
// 	delimitors.push_back (')');
// 	while (next->type != TokenType::PAR_R) {
// 	    if (next->type == TokenType::COMMA) {
// 		if (!params) {
// 		    throw SyntaxErrorException (next->value->to_string(), Position (next->line, next->column));
// 		}
// 	    }

// 	    if (!params)
// 		params = new vector<ast::Expression*> ();

// 	    params->push_back (visitExpression (&delimitors));

// 	    next = pop();
// 	    if (next->type != TokenType::COMMA && next->type != TokenType::PAR_R)
// 		throw MissingErrorException (")", Position (next->line, next->column));
// 	}
//     }
//     return params;
// }

/**
   Return := return expression*;
*/
// ast::Ast * Syntax::visitReturn (TokenPtr token) {
//     ast::Position * pos = new ast::Position (token->line, token->column);
//     ast::Expression * expr = NULL;
//     if (front()->type != TokenType::SEMICOLON)
// 	expr = visitExpression ();
//     return new ast::Return (expr, pos);
// }

/**
   Break := break ident?;
*/
// ast::Ast * Syntax::visitBreak (TokenPtr token) {
//     ast::Position * pos = new ast::Position (token->line, token->column);
//     string * ident = NULL;
//     TokenPtr next = front();
//     if (next->type == TokenType::IDENT) {
// 	pop();
// 	ident = new string (next->value->to_string());
//     }
//     return new ast::Break (ident, pos);
// }

// ast::Expression * Syntax::visitExpression (vector<char> * delimitors) {
//     /* Transformation de l'expression en notation polonaise inversée */
//     queue<TokenPtr*> out;
//     stack<TokenPtr*> op;

//     TokenPtr current_token = front();
//     TokenPtr tmp = NULL;
//     int nb_par_l = 0;

//     while (is_part_of_expr(current_token)) {
// 	string val = current_token->value->to_string();

// 	if (TokenPtr::is_value(current_token) || TokenPtr::is_ident(current_token)) {
// 	    out.push(current_token);
// 	} else if (TokenPtr::is_par_l(current_token)) {
// 	    nb_par_l++;
// 	    op.push(current_token);
// 	} else if (TokenPtr::is_par_r(current_token)) {
// 	    if (delimitors && is_delimitor (')', delimitors)) {
// 		if (nb_par_l == 0) {
// 		    break;
// 		}
// 	    }
// 	    nb_par_l--;
// 	    tmp = op.top();
// 	    while (!TokenPtr::is_par_l(tmp) && op.size() > 0) {
// 		out.push(tmp);
// 		op.pop();
// 		if (op.size() > 0)
// 		    tmp = op.top();
// 	    }
// 	    if (!TokenPtr::is_par_l(tmp)) {
// 		throw SyntaxErrorException(tmp->value->to_string(), Position(tmp->line, tmp->column));
// 	    } else {
// 		op.pop();
// 	    }
// 	} else if (TokenPtr::is_binop(current_token)) {
// 	    if (op.size() == 0 || TokenPtr::is_par_l(op.top())) {
// 		op.push(current_token);
// 	    } else {
// 		ast::Operator op1(current_token->value->to_string());
// 		ast::Operator op2(op.top()->value->to_string());
// 		if (op1.priority > op2.priority) {
// 		    op.push(current_token);
// 		} else {
// 		    out.push(op.top());
// 		    op.pop();
// 		    op.push(current_token);
// 		}
// 	    }
// 	} else {
// 	    throw SyntaxErrorException(current_token->value->to_string(), Position(current_token->line, current_token->column));
// 	}

// 	pop();
// 	TokenPtr last = current_token;
// 	current_token = front();

// 	if (current_token == NULL)
// 	    throw MissingErrorException(";", Position(last->line, last->column));
//     }

//     while (op.size() > 0) {
// 	out.push(op.top());
// 	op.pop();
//     }

//     /* On prendl la sortie et créé l'ast relatif à l'expression */
//     stack<ast::Expression*> st;

//     while (out.size() > 0) {
// 	TokenPtr t = out.front();
// 	out.pop();
// 	if (TokenPtr::is_value(t)) {
// 	    st.push(Syntax::create_value(t));
// 	} else if (TokenPtr::is_ident(t)) {
// 	    st.push(new ast::VarId(t->value->to_string(), new ast::Position(t->line, t->column)));
// 	} else {
// 	    ast::Operator * op = new ast::Operator(t->value->to_string());
// 	    ast::Expression * e2 = st.top();
// 	    st.pop();
// 	    ast::Expression * e1 = st.top();
// 	    st.pop();
// 	    st.push(new ast::Binop(e1, e2, op, new ast::Position(t->line, t->column)));
// 	}
//     }
//     if (st.size() != 1)
// 	throw MissingErrorException("operator", Position(st.top()->pos->line, st.top()->pos->column));

//     return st.top();
// }

// ast::Expression * Syntax::create_value(TokenPtr token) {
//     ast::Position * pos = new ast::Position(token->line, token->column);
//     TokenPtrValue * token_value = token->value;
//     switch (token->type) {
//     case TokenType::INT:
// 	return new ast::ConstInt(((TokenPtrIntValue*)token_value)->value, pos);
// 	break;
//     case TokenType::CHAR:
// 	return new ast::ConstChar(((TokenPtrCharValue*)token_value)->value, pos);
// 	break;
//     case TokenType::BOOL:
// 	return new ast::ConstBool(((TokenPtrBoolValue*)token_value)->value, pos);
// 	break;
//     default:
// 	cout << "tok " << token->to_string() << endl;
// 	throw SyntaxErrorException(token->value->to_string(), Position(token->line, token->column));
//     }
//     return NULL;
// }

// bool Syntax::is_part_of_expr (TokenPtr token) const {
//     return token->type >= 0 && token->type <= 20;
// }

// bool Syntax::is_delimitor (char c, vector<char> * delimitors) {
//     for (int i = 0; i < delimitors->size(); i++) {
// 	if ((*delimitors)[i] == c)
// 	    return true;
//     }
//     return false;
// }
