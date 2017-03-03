#include "Syntax.hpp"

using namespace std;
using namespace nyx;
using namespace ast;

Syntax::Syntax(Lexer & lex) : m_lex(lex) {
    m_table = symbol::Table::getInstance();
    m_program = visitBloc (true);
}

Syntax::~Syntax() {
}

TokenPtr Syntax::pop() const {
    return m_lex.next ();
}

void Syntax::rewind (int count) {
    m_lex.rewind (count);
}

AstPtr Syntax::getAst () const { return m_program; }

/**
   bloc := '{'? instruction* '}'?
*/
AstPtr Syntax::visitBloc (bool global) {
    vector<AstPtr> * instr = new vector<AstPtr> ();
    TokenPtr next = pop ();
    TokenPtr begin = next;
    if (begin->type == TokenType::ACCOL_L)
    	next = pop();
    while (next->type != TokenType::_EOF_ && next->type != TokenType::ACCOL_R) {
    	rewind ();
    	switch (next->type) {
    	case TokenType::LET:
	case TokenType::CONST:
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

    if (global)
	return Ast::New<Bloc> (instr, true);
    return Ast::New<Bloc> (instr);
}

/**
   instruction := (FunDecl | VarDecl | FunCall | VarAssign | Syscall);
*/
AstPtr Syntax::visitInstruction () {
    AstPtr res = NULL;
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
AstPtr Syntax::visitFunDecl (TokenPtr token_type, TokenPtr token_ident) {
    if (!isIdent (token_ident->value))
	throw MissingErrorException ("var name", Position (token_ident->line, token_ident->column));

    pop (); // '('
    TokenPtr next = pop ();
    vector <VarDeclPtr> * params = NULL;
    if (next->type != TokenType::PAR_R) {
	rewind ();
	params = visitParamsDecl ();
    }

    next = pop ();
    if (next->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position (next->line, next->column));

    rewind ();
    BlocPtr content = visitBloc ();
    Type * type = new Type (token_type->value, true);
    string ident = token_ident->value;
    Position * pos = new Position (token_type->line, token_type->column);

    return Ast::New<Function> (type, ident, params, content, pos);
}

/**
   params := (type ident*))
*/
vector <VarDeclPtr> * Syntax::visitParamsDecl () {
    vector <VarDeclPtr> * params = new vector <VarDeclPtr> ();
    TokenPtr next;
    do {
	TokenPtr type = pop ();
	if (type->type != TokenType::OTHER)
	    throw SyntaxErrorException (type->value, Position (type->line, type->column));
	VarIdPtr var_id = visitIdent ();
	next = pop ();
	if (var_id == NULL) {
	    throw SyntaxErrorException (next->value, Position (next->line, next->column));
	}
	if (next->type != TokenType::COMMA && next->type != TokenType::PAR_R)
	    throw MissingErrorException (")", Position (next->line, next->column));

	Type * ast_type = new Type (type->value, true);
	Position * pos = new Position (type->line, type->column);
	params->push_back (Instruction::New<VarDecl> (ast_type, var_id, pos));
    } while (next->type == TokenType::COMMA);
    return params;
}

/**
   funcall := ident ( params* )
*/
AstPtr Syntax::visitFunCall (TokenPtr token_ident) {
    vector<ExpressionPtr> * params = visitParams ();
    Position * pos = new Position (token_ident->line, token_ident->column);
    return Instruction::New<FunCall> (token_ident->value, params, pos);
}

ExpressionPtr Syntax::visitExprFunCall (TokenPtr token_ident) {
    vector<ExpressionPtr> * params = visitParams ();
    Position * pos = new Position (token_ident->line, token_ident->column);
    return Expression::New<FunCall> (token_ident->value, params, pos);
}

/**
   varDecl := let (ident (= expression),)+;
*/
AstPtr Syntax::visitLet () {
    pop (); // let
    return visitVarDecl (pop ());
}

AstPtr Syntax::visitVarDecl (TokenPtr token_ident) {
    if (!isIdent (token_ident->value))
	throw MissingErrorException ("var name", Position (token_ident->line, token_ident->column));
    VarIdPtr var_id = Expression::New<VarId> (token_ident->value, new Position (token_ident->line, token_ident->column));
    Position * pos = new Position (token_ident->line, token_ident->column);
    VarDeclPtr var_decl = Instruction::New<VarDecl> (var_id, pos);

    /* A vector to get multiple var declare */
    vector<AstPtr> * instr = new vector<AstPtr> ();
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
    return Ast::New<Bloc> (instr);
}

/**
   varAssign := ident = expression;
*/
AstPtr Syntax::visitVarAssign (TokenPtr token_ident, TokenPtr token_op) {
    Position * pos = new Position (token_ident->line, token_ident->column);
    ExpressionPtr e1 = Expression::New<VarId> (token_ident->value, pos);
    ExpressionPtr e2 = visitExpression ();
    Operator * op = new Operator (token_op->value);
    return Expression::New<Binop> (e1, e2, op, new Position (token_op->line, token_op->column));
}

/**
   ifElse := if (expression) { bloc } (else (if (expression))? { bloc })*
*/
AstPtr Syntax::visitIfElse () {
    TokenPtr token_if = pop ();
    TokenPtr next = pop ();

    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));

    ExpressionPtr expr_condition = visitExpression ();
    Position * pos = new Position (token_if->line, token_if->column);

    next = pop ();
    if (next->type != TokenType::PAR_R)
	throw MissingErrorException (")", Position (next->line, next->column));

    next = pop ();
    if (next->type != TokenType::ACCOL_L) {
	throw MissingErrorException ("{", Position (next->line, next->column));
    }

    AstPtr bloc_if = visitBloc ();

    next = pop ();
    if (next->type == TokenType::ELSE) {
	next = pop();
	AstPtr bloc_else;
	if (next->type == TokenType::ACCOL_L) {
	    bloc_else = visitBloc ();
	} else if (next->type == TokenType::IF) {
	    rewind ();
	    bloc_else = visitIfElse ();
	} else {
	    throw MissingErrorException ("{", Position (next->line, next->column));
	}
	return Instruction::New<IfElse> (expr_condition, bloc_if, bloc_else, pos);
    } else {
	rewind ();
	return Instruction::New<IfElse> (expr_condition, bloc_if, pos);
    }
}

/**
   For := for (i in 0 .. 10) { bloc }*/
AstPtr Syntax::visitFor () {
    TokenPtr token_for = pop ();
    TokenPtr next = pop();
    TokenPtr ident = NULL;
    VarIdPtr var_loop;

    if (next->type == TokenType::COLON) {
	next = pop();
	if (next->type != TokenType::OTHER)
	    throw MissingErrorException ("ident", Position (next->line, next->column));
	ident = next;
	next = pop();
    }
    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));

    var_loop = visitIdent ();
    if (var_loop == NULL) {
	next = pop ();
	throw SyntaxErrorException (next->value, Position (next->line, next->column));
    }

    next = pop();
    if (next->type != TokenType::IN)
	throw MissingErrorException ("in", Position (next->line, next->column));

    ExpressionPtr expr = visitExpression ();

    if (pop()->type != TokenType::PAR_R)
	throw MissingErrorException (")", Position(next->line, next->column));
    if (pop()->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position(next->line, next->column));

    rewind ();
    BlocPtr for_bloc = visitBloc ();
    Position * pos = new Position (token_for->line, token_for->column);
    string * id = ident ? new string (ident->value) : NULL;

    return Instruction::New<For> (id, var_loop, expr, for_bloc, pos);
}

/**
   While := While ( expr ) { bloc }
*/
AstPtr Syntax::visitWhile () {
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

    ExpressionPtr expr = visitExpression ();

    next = pop ();
    if (next->type != TokenType::PAR_R)
	throw MissingErrorException (")", Position (next->line, next->column));

    next = pop ();
    if (next->type != TokenType::ACCOL_L)
	throw MissingErrorException ("{", Position (next->line, next->column));
    rewind ();

    BlocPtr bloc = visitBloc ();
    Position * pos = new Position (token_while->line, token_while->column);
    string * id = ident ? new string (ident->value) : NULL;

    return Instruction::New<While> (id, expr, bloc, pos);
}

/**
   syscall := $ident ( params* );
*/
AstPtr Syntax::visitSyscall (TokenPtr token_ident) {
    vector<ExpressionPtr> * params = visitParams ();
    Position * pos = new Position (token_ident->line, token_ident->column);
    return Instruction::New<Syscall> (token_ident->value, params, pos);
}

// AstPtr Syntax::visitExprSyscall (TokenPtr token_ident) {
//     vector<ExpressionPtr> * params = visitParams ();
//     Position * pos = new Position (token_ident->line, token_ident->column);
//     return Instruction::New<Syscall> (token_ident->value, params, pos);
// }

/**
   params := (varid*)
*/
vector<ExpressionPtr> * Syntax::visitParams () {
    TokenPtr next = pop();
    if (next->type != TokenType::PAR_L)
	throw MissingErrorException ("(", Position (next->line, next->column));
    next = pop ();
    vector<ExpressionPtr> * params = NULL;
    if (next->type != TokenType::PAR_R) {
	while (next->type != TokenType::PAR_R) {
	    if (next->type == TokenType::COMMA) {
		if (!params) {
		    throw SyntaxErrorException (next->value, Position (next->line, next->column));
		}
		ExpressionPtr expr = visitExpression ();
		if (expr == NULL)
		    throw SyntaxErrorException (",", Position (next->line, next->column));
		params->push_back (expr);
	    } else {
		rewind ();
		if (!params)
		    params = new vector<ExpressionPtr> ();
		ExpressionPtr expr = visitExpression ();
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
AstPtr Syntax::visitReturn () {
    TokenPtr token_return = pop ();
    Position * pos = new Position (token_return->line, token_return->column);
    ExpressionPtr expr;
    if (pop()->type != TokenType::SEMICOLON) {
	rewind ();
	expr = visitExpression ();
    } else {
	rewind ();
    }
    return Instruction::New<Return> (expr, pos);
}

/**
   Break := break ident?;
*/
AstPtr Syntax::visitBreak () {
    TokenPtr token_break = pop ();
    Position * pos = new Position (token_break->line, token_break->column);
    string * ident = NULL;
    TokenPtr next = pop ();
    if (next->type == TokenType::OTHER) {
	ident = new string (next->value);
    } else {
	rewind ();
    }
    return Instruction::New<Break> (ident, pos);
}

ExpressionPtr Syntax::visitExpression () {
    return visitULow ();
}

ExpressionPtr Syntax::visitULow () {
    ExpressionPtr left = visitLow ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {ASSIGN, LE, GE, NE, PLUSEQ, MINUSEQ, MULEQ, DIVEQ, MODEQ})) {
	ExpressionPtr right = visitLow ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	Position * pos = new Position (next_op->line, next_op->column);
	Operator * op = new Operator (next_op->value);
	return visitULow (Expression::New<Binop> (left, right, op, pos));
    }
    rewind ();
    return left;
}

ExpressionPtr Syntax::visitULow (ExpressionPtr left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {ASSIGN, LE, GE, NE, PLUSEQ, MINUSEQ, MULEQ, DIVEQ, MODEQ})) {
	ExpressionPtr right = visitLow ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	Position * pos = new Position (next_op->line, next_op->column);
	Operator * op = new Operator (next_op->value);
	return visitULow (Expression::New<Binop> (left, right, op, pos));
    }
    rewind ();
    return left;
}


ExpressionPtr Syntax::visitLow () {
    ExpressionPtr left = visitHigh ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {LT, GT, EQ, AND, OR})) {
	ExpressionPtr right = visitHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	Position * pos = new Position (next_op->line, next_op->column);
	Operator * op = new Operator (next_op->value);
	return visitLow (Expression::New<Binop> (left, right, op, pos));
    }
    rewind ();
    return left;
}

ExpressionPtr Syntax::visitLow (ExpressionPtr left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {LT, GT, EQ, AND, OR})) {
	ExpressionPtr right = visitHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	Position * pos = new Position (next_op->line, next_op->column);
	Operator * op = new Operator (next_op->value);
	return visitLow (Expression::New<Binop> (left, right, op, pos));
    }
    rewind ();
    return left;
}

ExpressionPtr Syntax::visitHigh () {
    ExpressionPtr left = visitHHigh ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {PLUS, MINUS})) {
	ExpressionPtr right = visitHHigh ();
	if (right == NULL) {
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	}
	Position * pos = new Position (next_op->line, next_op->column);
	Operator * op = new Operator (next_op->value);
	return visitHigh (Expression::New<Binop> (left, right, op, pos));
    }
    rewind ();
    return left;
}

ExpressionPtr Syntax::visitHigh (ExpressionPtr left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {PLUS, MINUS})) {
	ExpressionPtr right = visitHHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	Position * pos = new Position (next_op->line, next_op->column);
	Operator * op = new Operator (next_op->value);
	return visitHigh (Expression::New<Binop> (left, right, op, pos));
    }
    rewind ();
    return left;
}

ExpressionPtr Syntax::visitHHigh () {
    ExpressionPtr left = visitHHHigh ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {MUL, DIV, MOD})) {
	ExpressionPtr right = visitHHHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	Position * pos = new Position (next_op->line, next_op->column);
	Operator * op = new Operator (next_op->value);
	return visitHHigh (Expression::New<Binop> (left, right, op, pos));
    }
    rewind ();
    return left;
}

ExpressionPtr Syntax::visitHHigh (ExpressionPtr left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {MUL, DIV, MOD})) {
	ExpressionPtr right = visitHHHigh ();
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	Position * pos = new Position (next_op->line, next_op->column);
	Operator * op = new Operator (next_op->value);
	return visitHHigh (Expression::New<Binop> (left, right, op, pos));
    }
    rewind ();
    return left;
}

ExpressionPtr Syntax::visitHHHigh () {
    ExpressionPtr left = visitLeft ();

    TokenPtr next_op = pop ();
    if (find (next_op->type, {POINT, BRACKET_L})) {
	ExpressionPtr right;
	if (next_op->type == TokenType::POINT) {
	    right = visitLeft ();
	} else {
	    right = visitIndex ();
	}
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	Position * pos = new Position (next_op->line, next_op->column);
	if (next_op->type == TokenType::POINT) {
	    Operator * op = new Operator (next_op->value);
	    return visitHHHigh (Expression::New<Binop> (left, right, op, pos));
	} else {
	    return visitHHHigh (Expression::New<Index> (left, right, pos));
	}
    }
    rewind ();
    return left;
}

ExpressionPtr Syntax::visitHHHigh (ExpressionPtr left) {
    TokenPtr next_op = pop ();
    if (find (next_op->type, {POINT, BRACKET_L})) {
	ExpressionPtr right;
	if (next_op->type == TokenType::POINT) {
	    right = visitLeft ();
	} else {
	    right = visitIndex ();
	}
	if (right == NULL)
	    throw MissingErrorException ("expression", Position (next_op->line, next_op->column));
	Position * pos = new Position (next_op->line, next_op->column);
	if (next_op->type == TokenType::POINT) {
	    Operator * op = new Operator (next_op->value);
	    return visitHHHigh (Expression::New<Binop> (left, right, op, pos));
	} else {
	    return visitHHHigh (Expression::New<Index> (left, right, pos));
	}
    }
    rewind ();
    return left;
}


ExpressionPtr Syntax::visitLeft () {
    ExpressionPtr elem;
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
    return NullExpression ();
}

ExpressionPtr Syntax::visitIndex () {
    ExpressionPtr expr = visitExpression ();
    TokenPtr next = pop ();
    if (next->type != TokenType::BRACKET_R)
	throw MissingErrorException ("]", Position (next->line, next->column));
    return expr;
}

ExpressionPtr Syntax::visitConst () {
    ExpressionPtr elem;
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
    return NullExpression ();
}

ExpressionPtr Syntax::visitFloat () {
    TokenPtr next = pop ();
    if (next->type == TokenType::POINT) {
	TokenPtr val = pop ();
	for (int i = 0; i < val->value.size (); i++) {
	    if (val->value[i] < '0' || val->value[i] > '9') {
		throw SyntaxErrorException (val->value, Position (val->line, val->column));
	    }
	}
	float res = (float)stoi (val->value);
	return Expression::New<Float> (res, new Position (next->line, next->column));
    } else {
	for (int i = 0; i < next->value.size (); i++) {
	    if (next->value[i] < '0' || next->value[i] > '9') {
		rewind ();
		return NullExpression ();
	    }
	}
	string res = next->value;
	TokenPtr float_token = next;
	next = pop ();
	if (next->type != TokenType::POINT) {
	    rewind (2);
	    return NullExpression ();
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
	return Expression::New<Float> (value, new Position (float_token->line, float_token->column));
    }
}

ExpressionPtr Syntax::visitBool () {
    TokenPtr next = pop ();
    if (next->type == TokenType::TRUE)
	return Expression::New<Bool> (true, new Position (next->line, next->column));
    if (next->type == TokenType::FALSE)
	return Expression::New<Bool> (false, new Position (next->line, next->column));
    rewind ();
    return NullExpression ();
}

ExpressionPtr Syntax::visitChar () {
    TokenPtr next = pop ();
    if (next->type != TokenType::SINGLE_QUOTE) {
	rewind ();
	return NullExpression ();
    }
    TokenPtr first = next;
    next = pop ();
    if (next->value.size () != 1)
	throw SyntaxErrorException (next->value, Position (next->line, next->column));
    char res = next->value[0];
    next = pop ();
    if (next->type != TokenType::SINGLE_QUOTE)
	throw MissingErrorException ("'", Position (next->line, next->column));
    return Expression::New<Char> (res, new Position (first->line, first->column));
}

ExpressionPtr Syntax::visitString () {
    TokenPtr next = pop ();
    TokenPtr start = next;
    if (next->type != TokenType::DOUBLE_QUOTE) {
	rewind ();
	return NullExpression ();
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

    Position * pos = new Position (next->line, next->column);
    return Expression::New<String> (str.str (), pos);
}

ExpressionPtr Syntax::visitInt () {
    TokenPtr next = pop ();
    for (int i = 0; i < next->value.size (); i++) {
	if (next->value[i] < '0' || next->value[i] > '9') {
	    rewind ();
	    return NullExpression ();
	}
    }
    return Expression::New<Int> (stoi (next->value), new Position (next->line, next->column));
}

/**
   Visite un identifiant (variable, appel de fonction ou de syscall)
 */
ExpressionPtr Syntax::visitIdent () {
    TokenPtr first = pop ();
    TokenPtr ident;

    if ((first->value[0] < 'A' || (first->value[0] > 'Z' && first->value[0] < 'a') || first->value[0] > 'z')
	&& first->value[0] != '_' && first->value[0] != '$') {
	rewind ();
	return NullExpression ();
    }

    if (first->type == TokenType::DOLLAR) {
	ident = pop ();
    } else {
	ident = first;
    }

    if (!isIdent (ident->value) || ident->type != TokenType::OTHER) {
	rewind ();
	return NullExpression ();
    }

    TokenPtr next = pop ();
    if (next->type == TokenType::PAR_L) {
	rewind ();
	// if (first->type == TokenType::DOLLAR) {
	//     return visitSyscall (ident);
	// }
	return visitExprFunCall (ident);
    }
    rewind ();
    return Expression::New<VarId> (ident->value, new Position (ident->line, ident->column));
}

ExpressionPtr Syntax::visitIdent (TokenPtr token_ident) {
    if (token_ident->type == TokenType::OTHER) {
	if ((token_ident->value[0] < 'A' || (token_ident->value[0] > 'Z' && token_ident->value[0] < 'a') || token_ident->value[0] > 'z') && token_ident->value[0] != '_') {
	    rewind ();
	    return NullExpression ();
	}
	for (int i = 0; i < token_ident->value.size (); i++) {
	    if (token_ident->value[i] < 'A' || (token_ident->value[i] > 'Z' && token_ident->value[i] < 'a') || token_ident->value[i] > 'z') {
		rewind ();
		return NullExpression ();
	    }
	}
	return Expression::New<VarId> (token_ident->value, new Position (token_ident->line, token_ident->column));
    }
    rewind ();
    return NullExpression ();
}

ExpressionPtr Syntax::visitUnaryOp () {
    TokenPtr op = pop ();
    if (!find (op->type, {NOT, NEW, MINUS})) {
	rewind ();
	return NullExpression ();
    }

    Operator * ope = new Operator (op->value);
    Position * pos = new Position (op->line, op->column);
    ExpressionPtr elem;

    TokenPtr next = pop ();
    if (next->type == TokenType::PAR_L) {
	elem = visitExpression ();
	next = pop ();
	if (next->type != TokenType::PAR_R)
	    throw MissingErrorException (")", Position (next->line, next->column));
	return Expression::New<UnOp> (ope, elem, pos);
    } else {
	rewind ();
    }

    if ((elem = visitIdent ()) != NULL)
	return Expression::New<UnOp> (ope, elem, pos);
    if ((elem = visitConst ()) != NULL)
    	return Expression::New<UnOp> (ope, elem, pos);
    if ((elem = visitUnaryOp ()) != NULL)
	return Expression::New<UnOp> (ope, elem, pos);
    return NullExpression ();
}

/**
   cast:type (expr);
 */
ExpressionPtr Syntax::visitCast () {
    TokenPtr token_cast = pop ();
    TokenPtr token_type;
    TokenPtr next;
    ExpressionPtr expr;

    if (token_cast->type != TokenType::CAST) {
	rewind ();
	return NullExpression ();
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

    Position * pos = new Position (token_cast->line, token_cast->column);
    Type * type = new Type (token_type->value);
    return Expression::New<Cast> (type, expr, pos);
}

ExpressionPtr Syntax::visitArray () {
    TokenPtr next = pop ();
    if (next->type != TokenType::BRACKET_L) {
	rewind ();
	return NullExpression ();
    }
    TokenPtr token_array = next;
    vector <ExpressionPtr> * array = new vector<ExpressionPtr> ();
    next = pop ();
    while (next->type != TokenType::BRACKET_R) {
	rewind ();
	ExpressionPtr expr = visitExpression ();
	if (expr == NULL) {
	    next = pop ();
	    throw SyntaxErrorException (next->value, Position (next->line, next->column));
	}

	next = pop ();
	//TODO : possible syntax error
	if (next->type == TokenType::DOUBLE_POINT) {
	    ExpressionPtr end = visitExpression ();
	    if (end == NULL)
		throw MissingErrorException ("expression .. expression", Position (next->line, next->column+2));
	    next = pop ();
	    if (next->type != TokenType::BRACKET_R)
		throw MissingErrorException ("]", Position (next->line, next->column));
	    Position * pos = new Position (token_array->line, token_array->column);
	    delete array;
	    return Expression::New<Range> (expr, end, pos);
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

    Position * pos = new Position (token_array->line, token_array->column);
    return Expression::New<Array> (array, pos);
}

AstPtr Syntax::visitImport () {
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
    return Instruction::New<Import> (path, new Position (token_import->line, token_import->column));
}


/**
   Class := class A ?(: B) { public { bloc } private { bloc } }
 */
AstPtr Syntax::visitClass () {
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

    FunctionPtr constructor = NULL;
    FunctionPtr destructor = NULL;
    BlocPtr public_bloc = NULL;
    BlocPtr private_bloc = NULL;
    vector<AstPtr> * public_content = NULL;
    vector<AstPtr> * private_content = NULL;

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
		    destructor = visitFunDecl (Token::make (type, {next->line, next->column}), next);
		    if (public_private->type == TokenType::PUBLIC) {
			if (!public_content)
			    public_content = new vector<AstPtr> ();
			public_content->push_back (destructor);
		    } else {
			if (!private_content)
			    private_content = new vector<AstPtr> ();
			private_content->push_back (destructor);
		    }
		} else if (next->type == TokenType::OTHER) {
		    if (next->value == "this") {
			string type = "void";
			constructor = visitFunDecl (Token::make (type, {next->line, next->column}), next);
			if (public_private->type == TokenType::PUBLIC) {
			    if (!public_content)
				public_content = new vector<AstPtr> ();
			    public_content->push_back (constructor);
			} else {
			    if (!private_content)
				private_content = new vector<AstPtr> ();
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
				    public_content = new vector<AstPtr> ();
				public_content->push_back (visitFunDecl (type, ident));
			    } else {
				if (!private_content)
				    private_content = new vector<AstPtr> ();
				private_content->push_back (visitFunDecl (type, ident));
			    }
			// } else if (next->type == TokenType::SEMICOLON || next->type == TokenType::ASSIGN) {
			//     rewind ();
			//     if (public_private->type == TokenType::PUBLIC) {
			// 	if (!public_content)
			// 	    public_content = new vector<AstPtr> ();
			// 	public_content->push_back (visitVarDecl (ident));
			//     } else {
			// 	if (!private_content)
			// 	    private_content = new vector<AstPtr> ();
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
	public_bloc = Ast::New<Bloc> (public_content);
    if (private_content)
	private_bloc = Ast::New<Bloc> (private_content);

    Position * pos = new Position (token_class->line, token_class->column);
    if (inheritance.size () > 0)
	return Ast::New<Class> (class_name, inheritance, constructor, destructor, public_bloc, private_bloc, pos);
    return Ast::New<Class> (class_name, constructor, destructor, public_bloc, private_bloc, pos);
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
