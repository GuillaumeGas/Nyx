#include "Syntax.hpp"

using namespace std;
using namespace nyx;
using namespace syntax;

Syntax::Syntax(Lexer & lex) : m_lex(lex) {
    m_table = symbol::Table::getInstance();
    m_program = visitBloc ();
}

Syntax::~Syntax() {}

TokenPtr Syntax::pop() const {
    return m_lex.next ();
}

void Syntax::rewind (int count) {
    m_lex.rewind (count);
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
	rewind ();
	switch (next->type) {
	case TokenType::LET:
	case TokenType::OTHER:
	case TokenType::DOLLAR:
	case TokenType::RETURN:
	case TokenType::BREAK:
	case TokenType::IMPORT:
	    instr->push_back (visitInstruction ());
	    break;
	case TokenType::IF:
	    instr->push_back (visitIfElse ());
	    break;
	case TokenType::FOR:
	    instr->push_back (visitFor ());
	    break;
	case TokenType::WHILE:
	    instr->push_back (visitWhile ());
	    break;
	case TokenType::CLASS:
	    instr->push_back (visitClass ());
	    break;
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
ast::Ast * Syntax::visitInstruction () {
    ast::Ast * res = NULL;
    TokenPtr token = pop ();
    TokenPtr next;
    if (token->type == TokenType::OTHER) {
	TokenPtr type = token;
	next = pop ();
	if (next->type == TokenType::OTHER) {
	    TokenPtr ident = next;
	    next = pop ();
	    rewind ();
	    if (next->type == TokenType::PAR_L) {
		return visitFunDecl (type, ident);
	    }
	} else if (next->type == TokenType::PAR_L) {
	    rewind ();
	    TokenPtr ident = type;
	    res = visitFunCall (ident);
	} else if (next->type == TokenType::ASSIGN) {
	    TokenPtr ident = type;
	    res = visitVarAssign (ident, next);
	} else {
	    rewind (2);
	    res = visitExpression ();
	}
    } else if (token->type == TokenType::LET) {
	rewind ();
	res = visitLet ();
    } else if (token->type == TokenType::RETURN) {
	rewind ();
    	res = visitReturn ();
    } else if (token->type == TokenType::BREAK) {
	rewind ();
    	res = visitBreak ();
    } else if (token->type == TokenType::DOLLAR) {
	res = visitSyscall (pop ());
    } else if (token->type == TokenType::IMPORT) {
	rewind ();
	res = visitImport ();
    } else {
	throw SyntaxErrorException (token->value, Position (token->line, token->column));
    }
    next = pop ();
    if (next->type != TokenType::SEMICOLON) {
	throw MissingErrorException (";", Position (next->line, next->column));
    }

    return res;
}

/**
   fundecl := type ident (params*) { bloc }
*/
ast::Ast * Syntax::visitFunDecl (TokenPtr token_type, TokenPtr token_ident) {
    if (!isIdent (token_ident->value))
	throw MissingErrorException ("var name", Position (token_ident->line, token_ident->column));

    pop (); // '('
    TokenPtr next = pop ();
    vector <ast::VarDecl*> * params = NULL;
    if (next->type != TokenType::PAR_R) {
	rewind ();
	params = visitParamsDecl ();
    }

    next = pop ();
    if (next->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position (next->line, next->column));

    rewind ();
    ast::Bloc * content = visitBloc ();
    ast::Type * type = new ast::Type (token_type->value, true);
    string ident = token_ident->value;
    ast::Position * pos = new ast::Position (token_type->line, token_type->column);

    return new ast::FunDecl (type, ident, params, content, pos);
}

/**
   params := (type ident*))
*/
vector <ast::VarDecl*> * Syntax::visitParamsDecl () {
    vector <ast::VarDecl*> * params = new vector <ast::VarDecl*> ();
    TokenPtr next;
    do {
	TokenPtr type = pop ();
	if (type->type != TokenType::OTHER)
	    throw SyntaxErrorException (type->value, Position (type->line, type->column));
	ast::VarId * var_id = (ast::VarId*)visitIdent ();
	next = pop ();
	if (var_id == NULL) {
	    throw SyntaxErrorException (next->value, Position (next->line, next->column));
	}
	if (next->type != TokenType::COMMA && next->type != TokenType::PAR_R)
	    throw MissingErrorException (")", Position (next->line, next->column));

	ast::Type * ast_type = new ast::Type (type->value, true);
	ast::Position * pos = new ast::Position (type->line, type->column);
	params->push_back (new ast::VarDecl (ast_type, var_id, pos));
    } while (next->type == TokenType::COMMA);
    return params;
}

/**
   funcall := ident ( params* )
*/
ast::Ast * Syntax::visitFunCall (TokenPtr token_ident) {
    vector<ast::Expression*> * params = visitParams ();
    ast::Position * pos = new ast::Position (token_ident->line, token_ident->column);
    return new ast::FunCall (token_ident->value, params, pos);
}

/**
   varDecl := let (ident (= expression),)+;
*/
ast::Bloc * Syntax::visitLet () {
    pop (); // let
    return visitVarDecl (pop ());
}

ast::Bloc * Syntax::visitVarDecl (TokenPtr token_ident) {
    if (!isIdent (token_ident->value))
	throw MissingErrorException ("var name", Position (token_ident->line, token_ident->column));
    ast::VarId * var_id = (ast::VarId*) new ast::VarId (token_ident->value, new ast::Position (token_ident->line, token_ident->column));
    ast::Position * pos = new ast::Position (token_ident->line, token_ident->column);
    ast::VarDecl * var_decl = new ast::VarDecl (var_id, pos);

    /* A vector to get multiple var declare */
    vector<ast::Ast*> * instr = new vector<ast::Ast*> ();
    instr->push_back (var_decl);

    TokenPtr next = pop ();
    if (next->type == TokenType::ASSIGN) {
	instr->push_back (visitVarAssign (token_ident, next));
	next = pop ();
    }
    if (next->type == TokenType::COMMA) {
	TokenPtr ident = pop ();
	if (ident->type != TokenType::OTHER) {
	    throw SyntaxErrorException (ident->value, Position (ident->line, ident->column));
	}
	instr->push_back (visitVarDecl (ident));
    } else {
	rewind ();
    }
    return new ast::Bloc (instr);
}

/**
   varAssign := ident = expression;
*/
ast::Ast * Syntax::visitVarAssign (TokenPtr token_ident, TokenPtr token_op) {
    ast::Position * pos = new ast::Position (token_ident->line, token_ident->column);
    ast::VarId * e1 = new ast::VarId (token_ident->value, pos);
    ast::Expression * e2 = visitExpression ();
    ast::Operator * op = new ast::Operator (token_op->value);
    return new ast::Binop (e1, e2, op, new ast::Position (token_op->line, token_op->column));
}

/**
   ifElse := if (expression) { bloc } (else (if (expression))? { bloc })*
*/
ast::Ast * Syntax::visitIfElse () {
    TokenPtr token_if = pop ();
    TokenPtr next = pop ();

    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));

    ast::Expression * expr_condition = visitExpression ();
    ast::Position * pos = new ast::Position (token_if->line, token_if->column);

    next = pop ();
    if (next->type != TokenType::PAR_R)
	throw MissingErrorException (")", Position (next->line, next->column));

    next = pop ();
    if (next->type != ACCOL_L) {
	throw MissingErrorException ("{", Position (next->line, next->column));
    }

    ast::Bloc * bloc_if = visitBloc ();

    next = pop ();
    if (next->type == TokenType::ELSE) {
	next = pop();
	ast::Bloc * bloc_else;
	if (next->type == TokenType::ACCOL_L) {
	    bloc_else = visitBloc ();
	} else if (next->type == TokenType::IF) {
	    rewind ();
	    bloc_else = (ast::Bloc*) visitIfElse ();
	} else {
	    throw MissingErrorException ("{", Position (next->line, next->column));
	}
	return new ast::IfElse (expr_condition, bloc_if, bloc_else, pos);
    } else {
	rewind ();
	return new ast::IfElse (expr_condition, bloc_if, pos);
    }
}

/**
   For := for (i in 0 .. 10) { bloc }*/
ast::Ast * Syntax::visitFor () {
    TokenPtr token_for = pop ();
    TokenPtr next = pop();
    TokenPtr ident = NULL;
    ast::VarId * var_loop;

    if (next->type == TokenType::COLON) {
	next = pop();
	if (next->type != TokenType::OTHER)
	    throw MissingErrorException ("ident", Position (next->line, next->column));
	ident = next;
	next = pop();
    }
    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));

    var_loop = (ast::VarId*)visitIdent ();
    if (var_loop == NULL) {
	next = pop ();
	throw SyntaxErrorException (next->value, Position (next->line, next->column));
    }

    next = pop();
    if (next->type != TokenType::IN)
	throw MissingErrorException ("in", Position (next->line, next->column));

    ast::Expression * expr = visitExpression ();

    if (pop()->type != TokenType::PAR_R)
	throw MissingErrorException (")", Position(next->line, next->column));
    if (pop()->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position(next->line, next->column));

    rewind ();
    ast::Bloc * for_bloc = visitBloc ();
    ast::Position * pos = new ast::Position (token_for->line, token_for->column);
    string * id = ident ? new string (ident->value) : NULL;

    return new ast::For (id, var_loop, expr, for_bloc, pos);
}

/**
   While := While ( expr ) { bloc }
*/
ast::Ast * Syntax::visitWhile () {
    TokenPtr token_while = pop ();
    TokenPtr ident = NULL;
    TokenPtr next = pop ();
    if (next->type == TokenType::COLON) {
	ident = pop();
	if (ident->type != TokenType::OTHER)
	    throw MissingErrorException ("ident", Position (ident->line, ident->column));
	next = pop ();
    }

    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));

    ast::Expression * expr = visitExpression ();

    next = pop ();
    if (next->type != TokenType::PAR_R)
	throw MissingErrorException (")", Position (next->line, next->column));

    next = pop ();
    if (next->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position (next->line, next->column));
    rewind ();

    ast::Bloc * bloc = visitBloc ();
    ast::Position * pos = new ast::Position (token_while->line, token_while->column);
    string * id = ident ? new string (ident->value) : NULL;

    return new ast::While (id, expr, bloc, pos);
}

/**
   syscall := $ident ( params* );
*/
ast::Ast * Syntax::visitSyscall (TokenPtr token_ident) {
    vector<ast::Expression*> * params = visitParams ();
    ast::Position * pos = new ast::Position (token_ident->line, token_ident->column);
    return new ast::Syscall (token_ident->value, params, pos);
}


/**
   params := (varid*)
*/
vector<ast::Expression*> * Syntax::visitParams () {
    TokenPtr next = pop();
    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));
    next = pop ();
    vector<ast::Expression*> * params = NULL;
    if (next->type != TokenType::PAR_R) {
	while (next->type != TokenType::PAR_R) {
	    if (next->type == TokenType::COMMA) {
		if (!params) {
		    throw SyntaxErrorException (next->value, Position (next->line, next->column));
		}
		ast::Expression * expr = visitExpression ();
		if (expr == NULL)
		    throw SyntaxErrorException (",", Position (next->line, next->column));
		params->push_back (expr);
	    } else {
		rewind ();
		if (!params)
		    params = new vector<ast::Expression*> ();
		ast::Expression * expr = visitExpression ();
		if (expr != NULL)
		    params->push_back (expr);
	    }

	    next = pop();
	    if (next->type != TokenType::COMMA && next->type != TokenType::PAR_R)
		throw MissingErrorException (")", Position (next->line, next->column));
	}
    }

    return params;
}

/**
   Return := return expression*;
*/
ast::Ast * Syntax::visitReturn () {
    TokenPtr token_return = pop ();
    ast::Position * pos = new ast::Position (token_return->line, token_return->column);
    ast::Expression * expr = NULL;
    if (pop()->type != TokenType::SEMICOLON) {
	rewind ();
	expr = visitExpression ();
    } else {
	rewind ();
    }
    return new ast::Return (expr, pos);
}

/**
   Break := break ident?;
*/
ast::Ast * Syntax::visitBreak () {
    TokenPtr token_break = pop ();
    ast::Position * pos = new ast::Position (token_break->line, token_break->column);
    string * ident = NULL;
    TokenPtr next = pop ();
    if (next->type == TokenType::OTHER) {
	ident = new string (next->value);
    } else {
	rewind ();
    }
    return new ast::Break (ident, pos);
}

ast::Expression * Syntax::visitExpression () {
    return visitULow ();
}

ast::Expression * Syntax::visitULow () {
    ast::Expression * left = visitLow ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {ASSIGN, LE, GE, NE, PLUSEQ, MINUSEQ, MULEQ, DIVEQ, MODEQ})) {
	ast::Expression * right = visitLow ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	ast::Operator * op = new ast::Operator (next_op->value);
	return visitULow (new ast::Binop (left, right, op, pos));
    }
    rewind ();
    return left;
}

ast::Expression * Syntax::visitULow (ast::Expression * left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {ASSIGN, LE, GE, NE, PLUSEQ, MINUSEQ, MULEQ, DIVEQ, MODEQ})) {
	ast::Expression * right = visitLow ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	ast::Operator * op = new ast::Operator (next_op->value);
	return visitULow (new ast::Binop (left, right, op, pos));
    }
    rewind ();
    return left;
}


ast::Expression * Syntax::visitLow () {
    ast::Expression * left = visitHigh ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {LT, GT, EQ, AND, OR})) {
	ast::Expression * right = visitHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	ast::Operator * op = new ast::Operator (next_op->value);
	return visitLow (new ast::Binop (left, right, op, pos));
    }
    rewind ();
    return left;
}

ast::Expression * Syntax::visitLow (ast::Expression * left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {LT, GT, EQ, AND, OR})) {
	ast::Expression * right = visitHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	ast::Operator * op = new ast::Operator (next_op->value);
	return visitLow (new ast::Binop (left, right, op, pos));
    }
    rewind ();
    return left;
}

ast::Expression * Syntax::visitHigh () {
    ast::Expression * left = visitHHigh ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {PLUS, MINUS})) {
	ast::Expression * right = visitHHigh ();
	if (right == NULL) {
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	}
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	ast::Operator * op = new ast::Operator (next_op->value);
	return visitHigh (new ast::Binop (left, right, op, pos));
    }
    rewind ();
    return left;
}

ast::Expression * Syntax::visitHigh (ast::Expression * left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {PLUS, MINUS})) {
	ast::Expression * right = visitHHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	ast::Operator * op = new ast::Operator (next_op->value);
	return visitHigh (new ast::Binop (left, right, op, pos));
    }
    rewind ();
    return left;
}

ast::Expression * Syntax::visitHHigh () {
    ast::Expression * left = visitHHHigh ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {MUL, DIV, MOD})) {
	ast::Expression * right = visitHHHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	ast::Operator * op = new ast::Operator (next_op->value);
	return visitHHigh (new ast::Binop (left, right, op, pos));
    }
    rewind ();
    return left;
}

ast::Expression * Syntax::visitHHigh (ast::Expression * left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {MUL, DIV, MOD})) {
	ast::Expression * right = visitHHHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	ast::Operator * op = new ast::Operator (next_op->value);
	return visitHHigh (new ast::Binop (left, right, op, pos));
    }
    rewind ();
    return left;
}

ast::Expression * Syntax::visitHHHigh () {
    ast::Expression * left = visitLeft ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {POINT, BRACKET_L})) {
	ast::Expression * right = NULL;
	if (next_op->type == TokenType::POINT) {
	    right = visitLeft ();
	} else {
	    right = visitIndex ();
	}
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	if (next_op->type == TokenType::POINT) {
	    ast::Operator * op = new ast::Operator (next_op->value);
	    return visitHHHigh (new ast::Binop (left, right, op, pos));
	} else {
	    return visitHHHigh (new ast::Index (left, right, pos));
	}
    }
    rewind ();
    return left;
}

ast::Expression * Syntax::visitHHHigh (ast::Expression * left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {POINT, BRACKET_L})) {
	ast::Expression * right = NULL;
	if (next_op->type == TokenType::POINT) {
	    right = visitLeft ();
	} else {
	    right = visitIndex ();
	}
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	if (next_op->type == TokenType::POINT) {
	    ast::Operator * op = new ast::Operator (next_op->value);
	    return visitHHHigh (new ast::Binop (left, right, op, pos));
	} else {
	    return visitHHHigh (new ast::Index (left, right, pos));
	}
    }
    rewind ();
    return left;
}


ast::Expression * Syntax::visitLeft () {
    ast::Expression * elem = NULL;
    TokenPtr next = pop ();

    if (next->type == TokenType::PAR_L) {
	elem = visitExpression  ();
	next = pop ();
	if (next->type != TokenType::PAR_R)
	    throw MissingErrorException (")", Position (next->line, next->column));
	return elem;
    } else {
	rewind ();
    }

    if ((elem = visitConst ()) != NULL)
	return elem;
    if ((elem = visitIdent ()) != NULL)
	return elem;
    if ((elem = visitUnaryOp ()) != NULL)
	return elem;
    if ((elem = visitCast ()) != NULL)
	return elem;
    return NULL;
}

ast::Expression * Syntax::visitIndex () {
    ast::Expression * expr = visitExpression ();
    TokenPtr next = pop ();
    if (next->type != TokenType::BRACKET_R)
	throw MissingErrorException ("]", Position (next->line, next->column));
    return expr;
}

ast::Expression * Syntax::visitConst () {
    ast::Expression * elem = NULL;
    if ((elem = visitString ()) != NULL)
	return elem;
    if ((elem = visitChar ()) != NULL)
	return elem;
    if ((elem = visitFloat ()) != NULL)
	return elem;
    if ((elem = visitInt ()) != NULL)
	return elem;
    if ((elem = visitBool ()) != NULL)
	return elem;
    if ((elem = visitArray ()) != NULL)
	return elem;
    return NULL;

}

ast::Expression * Syntax::visitFloat () {
    TokenPtr next = pop ();
    if (next->type == TokenType::POINT) {
	TokenPtr val = pop ();
	for (int i = 0; i < val->value.size (); i++) {
	    if (val->value[i] < '0' || val->value[i] > '9') {
		throw SyntaxErrorException (val->value, Position (val->line, val->column));
	    }
	}
	float res = (float)stoi (val->value);
	return new ast::Float (res, new ast::Position (next->line, next->column));
    } else {
	for (int i = 0; i < next->value.size (); i++) {
	    if (next->value[i] < '0' || next->value[i] > '9') {
		rewind ();
		return NULL;
	    }
	}
	string res = next->value;
	TokenPtr float_token = next;
	next = pop ();
	if (next->type != TokenType::POINT) {
	    rewind (2);
	    return NULL;
	}
	next = pop ();
	for (int i = 0; i < next->value.size (); i++) {
	    if (next->value[i] < '0' || next->value[i] > '9') {
		throw SyntaxErrorException (next->value, Position (next->line, next->column));
	    }
	}
	int left_part = next->value.size ();
	res += next->value;
	float value = (float)stoi (res);
	for (int i = 0; i < left_part; i++)
	    value /= 10;
	return new ast::Float (value, new ast::Position (float_token->line, float_token->column));
    }
}

ast::Expression * Syntax::visitBool () {
    TokenPtr next = pop ();
    if (next->type == TokenType::TRUE)
	return new ast::Bool (true, new ast::Position (next->line, next->column));
    if (next->type == TokenType::FALSE)
	return new ast::Bool (false, new ast::Position (next->line, next->column));
    rewind ();
    return NULL;
}

ast::Expression * Syntax::visitChar () {
    TokenPtr next = pop ();
    if (next->type != TokenType::SINGLE_QUOTE) {
	rewind ();
	return NULL;
    }
    TokenPtr first = next;
    next = pop ();
    if (next->value.size () != 1)
	throw SyntaxErrorException (next->value, Position (next->line, next->column));
    char res = next->value[0];
    next = pop ();
    if (next->type != TokenType::SINGLE_QUOTE)
	throw MissingErrorException ("'", Position (next->line, next->column));
    return new ast::Char (res, new ast::Position (first->line, first->column));
}

ast::Expression * Syntax::visitString () {
    TokenPtr next = pop ();
    TokenPtr start = next;
    if (next->type != TokenType::DOUBLE_QUOTE) {
	rewind ();
	return NULL;
    }

    m_lex.setSkipEnabled (" ", false);
    m_lex.setCommentsEnabled (false);

    stringstream str;
    while (next->type != TokenType::_EOF_) {
	next = pop ();
	if (next->type == TokenType::BACK_SLASH) {
	    str << next->value;
	    next = pop ();
	    str << next->value;
	    next = pop ();
	}
	if (next->type == TokenType::DOUBLE_QUOTE)
	    break;
	str << next->value;
    }
    if (next->type == TokenType::_EOF_) {
	throw MissingErrorException ("\"", Position (next->line, next->column));
    }

    m_lex.setCommentsEnabled (true);
    m_lex.setSkipEnabled (" ", true);

    ast::Position * pos = new ast::Position (next->line, next->column);
    return new ast::String (str.str (), pos);
}

ast::Expression * Syntax::visitInt () {
    TokenPtr next = pop ();
    for (int i = 0; i < next->value.size (); i++) {
	if (next->value[i] < '0' || next->value[i] > '9') {
	    rewind ();
	    return NULL;
	}
    }
    return new ast::Int (stoi (next->value), new ast::Position (next->line, next->column));
}

/**
   Visite un identifiant (variable, appel de fonction ou de syscall)
 */
ast::Expression * Syntax::visitIdent () {
    TokenPtr first = pop ();
    TokenPtr ident;

    if ((first->value[0] < 'A' || (first->value[0] > 'Z' && first->value[0] < 'a') || first->value[0] > 'z')
	&& first->value[0] != '_' && first->value[0] != '$') {
	rewind ();
	return NULL;
    }

    if (first->type == TokenType::DOLLAR) {
	ident = pop ();
    } else {
	ident = first;
    }

    if (!isIdent (ident->value) || ident->type != TokenType::OTHER) {
	rewind ();
	return NULL;
    }

    TokenPtr next = pop ();
    if (next->type == TokenType::PAR_L) {
	rewind ();
	if (first->type == TokenType::DOLLAR) {
	    return (ast::Expression*)visitSyscall (ident);
	}
	return (ast::Expression*)visitFunCall (ident);
    }
    rewind ();
    return new ast::VarId (ident->value, new ast::Position (ident->line, ident->column));
}

ast::Expression * Syntax::visitIdent (TokenPtr token_ident) {
    if (token_ident->type == TokenType::OTHER) {
	if ((token_ident->value[0] < 'A' || (token_ident->value[0] > 'Z' && token_ident->value[0] < 'a') || token_ident->value[0] > 'z') && token_ident->value[0] != '_') {
	    rewind ();
	    return NULL;
	}
	for (int i = 0; i < token_ident->value.size (); i++) {
	    if (token_ident->value[i] < 'A' || (token_ident->value[i] > 'Z' && token_ident->value[i] < 'a') || token_ident->value[i] > 'z') {
		rewind ();
		return NULL;
	    }
	}
	return new ast::VarId (token_ident->value, new ast::Position (token_ident->line, token_ident->column));
    }
    rewind ();
    return NULL;
}

ast::Expression * Syntax::visitUnaryOp () {
    TokenPtr op = pop ();
    if (!find (op->type, {NOT, NEW, MINUS})) {
	rewind ();
	return NULL;
    }

    ast::Operator * ope = new ast::Operator (op->value);
    ast::Position * pos = new ast::Position (op->line, op->column);
    ast::Expression * elem = NULL;

    TokenPtr next = pop ();
    if (next->type == TokenType::PAR_L) {
	elem = visitExpression ();
	next = pop ();
	if (next->type != TokenType::PAR_R)
	    throw MissingErrorException (")", Position (next->line, next->column));
	return new ast::UnOp (ope, elem, pos);
    } else {
	rewind ();
    }

    if ((elem = visitIdent ()) != NULL)
	return new ast::UnOp (ope, elem, pos);
    if ((elem = visitConst ()) != NULL)
	return new ast::UnOp (ope, elem, pos);
    if ((elem = visitUnaryOp ()) != NULL)
	return new ast::UnOp (ope, elem, pos);
    return NULL;
}

/**
   cast:type (expr);
 */
ast::Expression * Syntax::visitCast () {
    TokenPtr token_cast = pop ();
    TokenPtr token_type;
    TokenPtr next;
    ast::Expression * expr = NULL;

    if (token_cast->type != TokenType::CAST) {
	rewind ();
	return NULL;
    }

    next = pop ();
    if (next->type != TokenType::COLON)
	throw MissingErrorException (":", Position (next->line, next->column));

    next = pop ();
    if (next->type != TokenType::OTHER)
	throw SyntaxErrorException (next->value, Position (next->line, next->column));
    token_type = next;

    next = pop ();
    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));

    expr = visitExpression ();

    next = pop ();
    if (next->type != TokenType::PAR_R)
	throw MissingErrorException (")", Position (next->line, next->column));

    ast::Position * pos = new ast::Position (token_cast->line, token_cast->column);
    ast::Type * type = new ast::Type (token_type->value);
    return new ast::Cast (type, expr, pos);
}

ast::Expression * Syntax::visitArray () {
    TokenPtr next = pop ();
    if (next->type != TokenType::BRACKET_L) {
	rewind ();
	return NULL;
    }
    TokenPtr token_array = next;
    vector <ast::Expression*> * array = new vector <ast::Expression*> ();
    next = pop ();
    while (next->type != TokenType::BRACKET_R) {
	rewind ();
	ast::Expression * expr = visitExpression ();
	if (expr == NULL) {
	    next = pop ();
	    throw SyntaxErrorException (next->value, Position (next->line, next->column));
	}

	next = pop ();
	if (next->type == TokenType::DOUBLE_POINT) {
	    ast::Expression * end = visitExpression ();
	    if (end == NULL)
		throw MissingErrorException ("expression .. expression", Position (next->line, next->column+2));
	    next = pop ();
	    if (next->type != TokenType::BRACKET_R)
		throw MissingErrorException ("]", Position (next->line, next->column));
	    ast::Position * pos = new ast::Position (token_array->line, token_array->column);
	    return new ast::Range (expr, end, pos);
	}

	array->push_back (expr);

	if (next->type != TokenType::COMMA) {
	    if (next->type != TokenType::BRACKET_R) {
		throw MissingErrorException ("]", Position (next->line, next->column));
	    } else {
		rewind ();
	    }
	} else {
	    next = pop ();
	}
    }

    if (array->size () != 0)
	next = pop ();
    if (next->type != TokenType::BRACKET_R)
	throw MissingErrorException ("]", Position (next->line, next->column));

    ast::Position * pos = new ast::Position (token_array->line, token_array->column);
    return new ast::Array (array, pos);
}

ast::Ast * Syntax::visitImport () {
    TokenPtr token_import = pop ();
    TokenPtr next = pop ();
    vector<string> * path = new vector<string> ();
    while (next->type != TokenType::SEMICOLON) {
	path->push_back (next->value);
	next = pop ();
	if (next->type != TokenType::POINT &&
	    next->type != TokenType::SEMICOLON) {
	    throw MissingErrorException (".", Position (next->line, next->column));
	} else if (next->type == TokenType::POINT) {
	    next = pop ();
	}
    }
    if (path->size () == 0) {
	throw SyntaxErrorException ("Path missing.", Position (token_import->line, token_import->column));
    }
    rewind ();
    return new ast::Import (path, new ast::Position (token_import->line, token_import->column));
}


/**
   Class := class A ?(: B) { public { bloc } private { bloc } }
 */
ast::Ast * Syntax::visitClass () {
    TokenPtr token_class = pop ();
    TokenPtr next = pop ();

    string class_name, inheritance;

    if (!isIdent (next->value) || next->type != TokenType::OTHER)
	throw SyntaxErrorException (next->value, Position (next->line, next->column));
    class_name = next->value;

    next = pop ();
    if (next->type == TokenType::COLON) {
	next = pop ();
	if (!isIdent (next->value) || next->type != TokenType::OTHER)
	    throw SyntaxErrorException (next->value, Position (next->line, next->column));
	inheritance = next->value;
	next = pop ();
    }

    if (next->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position (next->line, next->column));

    ast::FunDecl * constructor = NULL;
    ast::FunDecl * destructor = NULL;
    ast::Bloc * public_bloc = NULL;
    ast::Bloc * private_bloc = NULL;
    vector<ast::Ast*> * public_content = NULL;
    vector<ast::Ast*> * private_content = NULL;

    next = pop ();
    while (next->type != TokenType::ACCOL_R) {
	if (next->type == TokenType::PUBLIC || next->type == TokenType::PRIVATE) {
	    TokenPtr public_private = next;
	    next = pop ();
	    if (next->type != TokenType::ACCOL_L)
		throw MissingErrorException ("{", Position (next->line, next->column));

	    next = pop ();
	    while (next->type != TokenType::ACCOL_R) {
		if (next->type == TokenType::TILDE) { //destructor
		    next = pop ();
		    TokenPtr this_ident = next;
		    if (next->value != "this")
			throw MissingErrorException ("this as destructor's name", Position (next->line, next->column));
		    string type = "void";
		    destructor = (ast::FunDecl*)visitFunDecl (Token::make (type, {next->line, next->column}), next);
		    if (public_private->type == TokenType::PUBLIC) {
			if (!public_content)
			    public_content = new vector<ast::Ast*> ();
			public_content->push_back (destructor);
		    } else {
			if (!private_content)
			    private_content = new vector<ast::Ast*> ();
			private_content->push_back (destructor);
		    }
		} else if (next->type == TokenType::OTHER) {
		    if (next->value == "this") {
			string type = "void";
			constructor = (ast::FunDecl*)visitFunDecl (Token::make (type, {next->line, next->column}), next);
			if (public_private->type == TokenType::PUBLIC) {
			    if (!public_content)
				public_content = new vector<ast::Ast*> ();
			    public_content->push_back (constructor);
			} else {
			    if (!private_content)
				private_content = new vector<ast::Ast*> ();
			    private_content->push_back (constructor);
			}
		    } else {
			TokenPtr type = next;
			next = pop ();
			if (next->type != TokenType::OTHER && !isIdent (next->value))
			    throw SyntaxErrorException (next->value, Position (next->line, next->column));
			TokenPtr ident = next;
			next = pop ();
			if (next->type == TokenType::PAR_L) {
			    rewind ();
			    if (public_private->type == TokenType::PUBLIC) {
				if (!public_content)
				    public_content = new vector<ast::Ast*> ();
				public_content->push_back (visitFunDecl (type, ident));
			    } else {
				if (!private_content)
				    private_content = new vector<ast::Ast*> ();
				private_content->push_back (visitFunDecl (type, ident));
			    }
			// } else if (next->type == TokenType::SEMICOLON || next->type == TokenType::ASSIGN) {
			//     rewind ();
			//     if (public_private->type == TokenType::PUBLIC) {
			// 	if (!public_content)
			// 	    public_content = new vector<ast::Ast*> ();
			// 	public_content->push_back (visitVarDecl (ident));
			//     } else {
			// 	if (!private_content)
			// 	    private_content = new vector<ast::Ast*> ();
			// 	private_content->push_back (visitVarDecl (type, ident));
			//     }
			//     pop ();
			} else {
			    throw SyntaxErrorException (next->value, Position (next->line, next->column));
			}
		    }
		} else {
		    throw SyntaxErrorException (next->value, Position (next->line, next->column));
		}
		next = pop ();
	    }
	} else {
	    throw MissingErrorException ("public or private statement", Position (next->line, next->column));
	}
	next = pop ();
    }

    if (public_content)
	public_bloc = new ast::Bloc (public_content);
    if (private_content)
	private_bloc = new ast::Bloc (private_content);

    ast::Position * pos = new ast::Position (token_class->line, token_class->column);
    if (inheritance.size () > 0)
	return new ast::Class (class_name, inheritance, constructor, destructor, public_bloc, private_bloc, pos);
    return new ast::Class (class_name, constructor, destructor, public_bloc, private_bloc, pos);
}


bool Syntax::find (TokenType type, vector <TokenType> list) {
    for (TokenType t : list) {
	if (t == type) return true;
    }
    return false;
}

bool Syntax::isIdent (string value) {
    if (value[0] < 'A' || value[0] > 'z' || (value[0] > 'Z' && value[0] < 'a'))
	return false;
    for (int i = 1; i < value.size (); i++) {
	if ((value[i] < 'A' || (value[i] > 'Z' && value[i] < 'a') || value[i] > 'z') && (value[i] < '0' || value[i] > '9') && value[i] != '_') {
	    return false;
	}
    }
    return true;
}
