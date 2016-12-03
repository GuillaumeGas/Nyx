#include <iostream>
#include <fstream>
#include <istream>

#include "Lexer.hpp"

using namespace std;

int main() {

    Lexer lex ("test.nx");
    lex.setKeys ({" ", "=", ";", "/*", "*/", "//", "\n"});
    lex.setSkips ({" ", "\n", "\t", "\r"});
    lex.setComs ({make_pair("/*", "*/"), make_pair("//", "\n")});
    int i = 0;

    Token t = lex.next();
    cout << t.toString() << endl;
    lex.rewind ();
    t = lex.next ();
    cout << t.toString() << endl;

    return 0;
}
