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
	res = visitSyscall (pop ());
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
	instr->push_back (visitVarDecl (token_type, ident));
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
    return visitLow ();
}

ast::Expression * Syntax::visitLow () {
    ast::Expression * left = visitHigh ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {LT, LE, GT, GE, EQ, NE, AND, OR})) {
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
    if (find (next_op->type, {LT, LE, GT, GE, EQ, AND, OR})) {
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
    return NULL;
}

ast::Expression * Syntax::visitConst () {
    ast::Expression * elem = NULL;
    if ((elem = visitString ()) != NULL)
	return elem;
    if ((elem = visitChar ()) != NULL)
	return elem;
    if ((elem = visitInt ()) != NULL)
	return elem;
    if ((elem = visitFloat ()) != NULL)
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
	for (int i = 0; i < val->value.size (); i++) res /= 10;
	return new ast::Float (res, new ast::Position (next->line, next->column));
    } else {
	//TODO
	rewind ();
	return NULL;
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
    if (next->type != TokenType::OTHER || next->value.size () > 1)
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
    return new ast::String (new string (str.str ()), pos);
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

    for (int i = 1; i < ident->value.size (); i++) {
	if (ident->value[i] < 'A' || (ident->value[i] > 'Z' && ident->value[i] < 'a') || ident->value[i] > 'z') {
	    if (first->type == TokenType::DOLLAR)
		throw SyntaxErrorException ("$", Position (first->line, first->column));
	    rewind ();
	    return NULL;
	}
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

ast::Expression * Syntax::visitArray () {
    TokenPtr next = pop ();
    if (next->type != TokenType::BRACKET_L) {
	rewind ();
	return NULL;
    }
    TokenPtr token_array = next;
    vector <ast::Expression*> * array = NULL;
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

	if (array == NULL)
	    array = new vector<ast::Expression*> ();

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

    next = pop ();
    if (next->type != TokenType::BRACKET_R)
	throw MissingErrorException ("]", Position (next->line, next->column));

    ast::Position * pos = new ast::Position (token_array->line, token_array->column);
    return new ast::Array (array, pos);
}

bool Syntax::find (TokenType type, vector <TokenType> list) {
    for (TokenType t : list) {
	if (t == type) return true;
    }
    return false;
}
