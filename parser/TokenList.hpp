#pragma once

/* TokenList example
#define LEX_TOKEN_LIST				\
    LEX_TOKEN (EXAMPLE_1, "ex1")		\
    // The lexer need theses following tokens !
    LEX_TOKEN (_EOF_, "<lex::eof>")		\
    LEX_TOKEN (OTHER, "<lex::other>")
*/

#define LEX_TOKEN_LIST				\
    LEX_TOKEN (PLUS, "+")			\
    LEX_TOKEN (PLUSPLUS, "++")			\
    LEX_TOKEN (MINUS, "-")			\
    LEX_TOKEN (MINUSMINUS, "--")		\
    LEX_TOKEN (MUL, "*")			\
    LEX_TOKEN (DIV, "/")			\
    LEX_TOKEN (MOD, "%")			\
    LEX_TOKEN (MODEQ, "%=")			\
    LEX_TOKEN (LT, "<")				\
    LEX_TOKEN (LE, "<=")			\
    LEX_TOKEN (GT, ">")				\
    LEX_TOKEN (GE, ">=")			\
    LEX_TOKEN (EQ, "==")			\
    LEX_TOKEN (NE, "!=")			\
    LEX_TOKEN (AND, "&&")			\
    LEX_TOKEN (OR, "||")			\
    LEX_TOKEN (NOT, "!")			\
    LEX_TOKEN (PAR_L, "(")			\
    LEX_TOKEN (PAR_R, ")")			\
    LEX_TOKEN (ASSIGN, "=")			\
    LEX_TOKEN (PLUSEQ, "+=")			\
    LEX_TOKEN (MINUSEQ, "-=")			\
    LEX_TOKEN (MULEQ, "*=")			\
    LEX_TOKEN (DIVEQ, "/=")			\
    LEX_TOKEN (ACCOL_L, "{")			\
    LEX_TOKEN (ACCOL_R, "}")			\
    LEX_TOKEN (BRACKET_L, "[")			\
    LEX_TOKEN (BRACKET_R, "]")			\
    LEX_TOKEN (SEMICOLON, ";")			\
    LEX_TOKEN (COMMA, ",")			\
    LEX_TOKEN (COLON, ":")			\
    LEX_TOKEN (POINT, ".")			\
    LEX_TOKEN (TILDE, "~")			\
    LEX_TOKEN (DOUBLE_POINT, "..")		\
    LEX_TOKEN (DOUBLE_QUOTE, "\"")		\
    LEX_TOKEN (SINGLE_QUOTE, "'")		\
    LEX_TOKEN (BACK_SLASH, "\\")		\
    LEX_TOKEN (LET, "let")			\
    LEX_TOKEN (IF, "if")			\
    LEX_TOKEN (ELSE, "else")			\
    LEX_TOKEN (WHILE, "while")			\
    LEX_TOKEN (DO, "do")			\
    LEX_TOKEN (FOR, "for")			\
    LEX_TOKEN (RETURN, "return")		\
    LEX_TOKEN (BREAK, "break")			\
    LEX_TOKEN (TRUE, "true")			\
    LEX_TOKEN (FALSE, "false")			\
    LEX_TOKEN (_NULL_, "null")			\
    LEX_TOKEN (IN, "in")			\
    LEX_TOKEN (CAST, "cast")			\
    LEX_TOKEN (DOLLAR, "$")			\
    LEX_TOKEN (IMPORT, "import")		\
    LEX_TOKEN (CLASS, "class")			\
    LEX_TOKEN (PRIVATE, "private")		\
    LEX_TOKEN (PUBLIC, "public")		\
    LEX_TOKEN (NEW, "new")			\
    LEX_TOKEN (SPACE, " ")			\
    LEX_TOKEN (COM_L, "/*")			\
    LEX_TOKEN (COM_R, "*/")			\
    LEX_TOKEN (COM_SIMPLE, "//")		\
    LEX_TOKEN (CR, "\n")			\
    LEX_TOKEN (_EOF_, "<lex::eof>")		\
    LEX_TOKEN (OTHER, "<lex::other>")
