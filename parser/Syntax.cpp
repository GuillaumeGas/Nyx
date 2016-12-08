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

void Syntax::rewind (int count) {
    lex.rewind (count);
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
	case TokenType::OTHER:
	case TokenType::DOLLAR:
	case TokenType::RETURN:
	case TokenType::BREAK:
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
	    } else if (next->type == TokenType::ASSIGN
		       || next->type == TokenType::SEMICOLON
		       || next->type == TokenType::COMMA) {
		res = visitVarDecl (type, ident);
	    }
	} else if (next->type == TokenType::PAR_L) {
	    rewind ();
	    TokenPtr ident = type;
	    res = visitFunCall (ident);
	} else if (next->type == TokenType::ASSIGN) {
	    TokenPtr ident = type;
	    res = visitVarAssign (ident, next);
	} else {
	    throw SyntaxErrorException (next->value, Position (next->line, next->column));
	}
    } else if (token->type == TokenType::RETURN) {
	rewind ();
    	res = visitReturn ();
    } else if (token->type == TokenType::BREAK) {
	rewind ();
    	res = visitBreak ();
    } else if (token->type == TokenType::DOLLAR) {
	res = visitSyscall ();
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
   varDecl := type (ident (= expression),)*;
*/
ast::Bloc * Syntax::visitVarDecl (TokenPtr token_type, TokenPtr token_ident) {
    ast::VarId * var_id = (ast::VarId*)visitIdent (token_ident);
    if (var_id == NULL)
	throw MissingErrorException ("var name", Position (token_ident->line, token_ident->column));
    ast::Position * pos = new ast::Position (token_type->line, token_type->column);
    ast::Type * type = new ast::Type (token_type->value, true);
    ast::VarDecl * var_decl = new ast::VarDecl (type, var_id, pos);

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
	instr->push_back (visitVarDecl (token_type, token_ident));
    }
    rewind ();
    return new ast::Bloc (instr);
}

/**
   varAssign := ident = expression;
*/
ast::Ast * Syntax::visitVarAssign (TokenPtr token_ident, TokenPtr token_op) {
    ast::Position * pos = new ast::Position (token_ident->line, token_ident->column);
    ast::Expression * e1 = new ast::VarId (token_ident->value, pos);
    ast::Expression * e2 = visitExpression ();
    ast::Operator * op = new ast::Operator (token_op->value);
    return new ast::VarAssign (e1, e2, op, new ast::Position (token_op->line, token_op->column));
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

    ast::Expression * expr_start = visitExpression ();

    next = pop ();
    if (next->type != TokenType::DOUBLE_POINT)
	throw SyntaxErrorException (next->value, Position (next->line, next->column));

    ast::Expression * expr_end = visitExpression ();

    if (pop()->type != TokenType::PAR_R)
	throw MissingErrorException (")", Position(next->line, next->column));
    if (pop()->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position(next->line, next->column));

    rewind ();
    ast::Bloc * for_bloc = visitBloc ();
    ast::Position * pos = new ast::Position (token_for->line, token_for->column);
    string * id = ident ? new string (ident->value) : NULL;

    return new ast::For (id, var_loop, expr_start, expr_end, for_bloc, pos);
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
ast::Ast * Syntax::visitSyscall () {
    TokenPtr token = pop ();
    vector<ast::Expression*> * params = visitParams ();
    ast::Position * pos = new ast::Position (token->line, token->column);
    return new ast::Syscall (token->value, params, pos);
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
		next = pop ();
	    }

	    if (!params)
		params = new vector<ast::Expression*> ();

	    rewind ();
	    params->push_back (visitExpression ());

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
    return visitLow ();
}

ast::Expression * Syntax::visitLow () {
    ast::Expression * left = visitHigh ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {LT, LE, GT, GE, EQ})) {
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
    if (find (next_op->type, {LT, LE, GT, GE, EQ})) {
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
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
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
    ast::Expression * left = visitLeft ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {MUL, DIV, MOD})) {
	ast::Expression * right = visitLeft ();
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
	ast::Expression * right = visitLeft ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	ast::Position * pos = new ast::Position (next_op->line, next_op->column);
	ast::Operator * op = new ast::Operator (next_op->value);
	return visitHHigh (new ast::Binop (left, right, op, pos));
    }
    rewind ();
    return left;
}

ast::Expression * Syntax::visitLeft () {
    ast::Expression * elem = NULL;
    if ((elem = visitConst ()) != NULL)
	return elem;
    if ((elem = visitIdent ()) != NULL)
	return elem;
    if ((elem = visitUnaryOp ()) != NULL)
	return elem;
    return NULL;
}

ast::Expression * Syntax::visitConst () {
    ast::Expression * elem = NULL;
    if ((elem = visitConstString ()) != NULL)
	return elem;
    if ((elem = visitConstChar ()) != NULL)
	return elem;
    if ((elem = visitConstInt ()) != NULL)
	return elem;
    if ((elem = visitConstFloat ()) != NULL)
	return elem;
    if ((elem = visitConstBool ()) != NULL)
	return elem;
    return NULL;

}
ast::Expression * Syntax::visitConstFloat () {
    TokenPtr next = pop ();
    if (next->type == TokenType::POINT) {
	TokenPtr val = pop ();
	for (int i = 0; i < val->value.size (); i++) {
	    if (val->value[i] < '0' || val->value[i] > '9') {
		throw SyntaxErrorException (val->value, Position (val->line, val->column));
	    }
	}
	float res = (float)stoi (val->value);
	for (int i = 0; i < val->value.size (); i++) res /= 10;
	return new ast::ConstFloat (res, new ast::Position (next->line, next->column));
    } else {
	//TODO
	rewind ();
	return NULL;
    }
}

ast::Expression * Syntax::visitConstBool () {
    TokenPtr next = pop ();
    if (next->type == TokenType::TRUE)
	return new ast::ConstBool (true, new ast::Position (next->line, next->column));
    if (next->type == TokenType::FALSE)
	return new ast::ConstBool (false, new ast::Position (next->line, next->column));
    rewind ();
    return NULL;
}

ast::Expression * Syntax::visitConstChar () {
    TokenPtr next = pop ();
    if (next->type != TokenType::SINGLE_QUOTE) {
	rewind ();
	return NULL;
    }
    TokenPtr first = next;
    next = pop ();
    if (next->type != TokenType::OTHER || next->value.size () > 1)
	throw SyntaxErrorException (next->value, Position (next->line, next->column));
    char res = next->value[0];
    next = pop ();
    if (next->type != TokenType::SINGLE_QUOTE)
	throw MissingErrorException ("'", Position (next->line, next->column));
    return new ast::ConstChar (res, new ast::Position (first->line, first->column));
}

ast::Expression * Syntax::visitConstString () {
    TokenPtr next = pop ();
    if (next->type != TokenType::DOUBLE_QUOTE) {
	rewind ();
	return NULL;
    }
    TODO ("ConstString");
}

ast::Expression * Syntax::visitConstInt () {
    TokenPtr next = pop ();
    for (int i = 0; i < next->value.size (); i++) {
	if (next->value[i] < '0' || next->value[i] > '9') {
	    rewind ();
	    return NULL;
	}
    }
    return new ast::ConstInt (stoi (next->value), new ast::Position (next->line, next->column));
}

ast::Expression * Syntax::visitIdent () {
    TokenPtr next = pop ();
    if ((next->value[0] < 'A' || (next->value[0] > 'Z' && next->value[0] < 'a') || next->value[0] > 'z') && next->value[0] != '_') {
	rewind ();
	return NULL;
    }
    for (int i = 0; i < next->value.size (); i++) {
	if (next->value[i] < 'A' || (next->value[i] > 'Z' && next->value[i] < 'a') || next->value[i] > 'z') {
	    rewind ();
	    return NULL;
	}
    }

    TokenPtr ident = next;
    next = pop ();
    if (next->type == TokenType::PAR_L) {
	rewind ();
	return (ast::Expression*)visitFunCall (ident);
    }
    rewind ();
    return new ast::VarId (ident->value, new ast::Position (ident->line, ident->column));
}

ast::Expression * Syntax::visitIdent (TokenPtr token_ident) {
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

ast::Expression * Syntax::visitUnaryOp () {
    TokenPtr op = pop ();
    if (!find (op->type, {NOT})) {
	rewind ();
	return NULL;
    }
    ast::Ast * next = NULL;
    if ((next = visitIdent ()) != NULL) {
	ast::Operator * ope = new ast::Operator (op->value);
	ast::Position * pos = new ast::Position (op->line, op->column);
	return new ast::UnOp (ope, (ast::Expression*)next, pos);
    }
    TokenPtr tok = pop ();
    if (tok->type != TokenType::PAR_L)
	throw SyntaxErrorException (tok->value, Position (tok->line, tok->column));
    return visitExpression ();
}

bool Syntax::find (TokenType type, vector <TokenType> list) {
    for (TokenType t : list) {
	if (t == type) return true;
    }
    return false;
}
