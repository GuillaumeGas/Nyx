#pragma once

#include <iostream>
#include <vector>

namespace nyx {
    enum TokenType {
	/*0 --> 20 -> May be part of an expression */
	INT,
	CHAR,
	BOOL,
	STRING,
	IDENT,
	PLUS,   // '+'
	PLUSPLUS, // '++'
	MINUS, // '-'
	MINUSMINUS, // '--'
	MUL, // '*'
	DIV, // '/'
	MOD, // '%'
	MODEQ, // '%='
	LT,  // '<'
	LE, // '<='
	GT,  // '>'
	GE, // '>='
	EQ,  // '=='
	NE, // '!='
	PAR_L, // '('
	PAR_R, // ')'
	/* Off part of an expression */
	ASSIGN, // '='
	PLUSEQ, // '+='
	MINUSEQ, // '-='
	MULEQ, // '*='
	DIVEQ, // '/='
	ACCOL_R, // '{'
	ACCOL_L, // '}'
	SEMICOLON, // ';'
	COMMA, // ,
	COLON, // :
	TYPE,
	IF,
	ELSE,
	ELSEIF,
	WHILE,
	DO,
	FOR,
	RETURN,
	BREAK,
	POINT,
	IN,
	SYSCALL,
	_EOF_,
    };

    struct TokenValue {
	virtual std::string to_string() const = 0;
    };

    struct TokenIntValue : TokenValue {
	TokenIntValue(int i);

	std::string to_string() const;

	int value;
    };
    struct TokenCharValue : TokenValue  {
	TokenCharValue(char c);

	std::string to_string() const;

	char value;
    };
    struct TokenStringValue : TokenValue  {
	TokenStringValue(std::string& s);

	std::string to_string() const;

	std::string value;
    };
    struct TokenBoolValue : TokenValue {
	TokenBoolValue(bool b);

	std::string to_string() const;

	bool value;
    };


    struct Token {
	Token(TokenType t, int v, unsigned int l, unsigned int col);
	Token(TokenType t, char c, unsigned int l, unsigned int col);
	Token(TokenType t, std::string& s, unsigned int l, unsigned int col);
	Token(TokenType t, bool b, unsigned int l, unsigned int col);
	~Token();

	std::string to_string() const;
	std::string type_to_string() const;

	TokenType type;
	TokenValue * value;

	unsigned int line;
	unsigned int column;

	static Token* create(std::string& token, unsigned int line, unsigned int col);
	static bool is_type(std::string& t);
	static bool is_ident(std::string& t);
	static bool is_assign(std::string& t);
	static bool is_integer(std::string& t);
	static bool is_semicolon(std::string& t);
	static bool is_colon (std::string& t);
	static bool is_comma (std::string& t);
	static bool is_char(std::string& t);
	static bool is_string(std::string& t);
	static bool is_bool(std::string& t);
	static bool is_plus(std::string& t);
	static bool is_plusplus(std::string& t);
	static bool is_pluseq(std::string& t);
	static bool is_minus(std::string& t);
	static bool is_minusminus(std::string& t);
	static bool is_minuseq(std::string& t);
	static bool is_mul(std::string& t);
	static bool is_muleq(std::string& t);
	static bool is_div(std::string& t);
	static bool is_diveq(std::string& t);
	static bool is_mod(std::string& t);
	static bool is_modeq(std::string& t);
	static bool is_lt(std::string& t);
	static bool is_le(std::string& t);
	static bool is_gt(std::string& t);
	static bool is_ge(std::string& t);

	static bool is_eq(std::string& t);
	static bool is_ne(std::string& t);
	static bool is_par_l(std::string& t);
	static bool is_par_r(std::string& t);
	static bool is_accol_l(std::string& t);
	static bool is_accol_r(std::string& t);
	static bool is_if(std::string& t);
	static bool is_else(std::string& t);
	static bool is_elseif(std::string& t);
	static bool is_do(std::string& t);
	static bool is_for(std::string& t);
	static bool is_while(std::string& t);
	static bool is_return(std::string& t);
	static bool is_break(std::string& t);
	static bool is_point(std::string& t);
	static bool is_in(std::string& t);
	static bool is_syscall (std::string& t);

	static bool is_value(Token * t);
	static bool is_ident(Token * t);
	static bool is_binop(Token * t);
	static bool is_par_l(Token * t);
	static bool is_par_r(Token * t);
    };

    struct TokenEof : Token {
	TokenEof ();
	std::string to_string() const;
    };

};
