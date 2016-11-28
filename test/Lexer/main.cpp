#include <iostream>
#include <fstream>
#include <istream>

#include "Lexer.hpp"

using namespace std;

int main() {

    Lexer lex ("test.nx");
    lex.setKeys ({" ", "=", ";"});
    int i = 0;
    while (!lex.isEof()) {
    	Token t = lex.next();
    	cout << t.to_string() << endl;
    }

    return 0;
}
