#pragma once

/* TokenList example
#define LEX_TOKEN_LIST				\
    LEX_TOKEN (EXAMPLE_1, "ex1")		\
    // The lexer need theses following tokens !
    LEX_TOKEN (_EOF_, "<lex::eof>")		\
    LEX_TOKEN (OTHER, "<lex::other>")
*/

#define LEX_TOKEN_LIST				\
    LEX_TOKEN (SPACE, " ")			\
    LEX_TOKEN (ASSIGN, "=")			\
    LEX_TOKEN (COLON, ";")			\
    LEX_TOKEN (COM_L, "/*")			\
    LEX_TOKEN (COM_R, "*/")			\
    LEX_TOKEN (COM_SIMPLE, "//")		\
    LEX_TOKEN (CR, "\n")			\
    LEX_TOKEN (_EOF_, "<lex::eof>")		\
    LEX_TOKEN (OTHER, "<lex::other>")
