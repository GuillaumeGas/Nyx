#include <iostream>
#include <fstream>
#include <istream>

#include "Lexer.hpp"

using namespace std;

// struct location_t {
//     unsigned int line;
//     unsigned int column;
// };

// struct Token {
//     string value;
//     location_t loc;
//     Token (string v, location_t l) : value (v), loc (l) {}
//     string to_string() { return "<" + value + ", loc (" + std::to_string(loc.line) + ", " + std::to_string(loc.column) + ")>"; }
// };

// class Test {
// public:
//     Test (string file_name) {
// 	file = new ifstream (file_name.c_str(), std::ios::in);
// 	index = 0;
// 	loc.line = 1;
// 	loc.column = 0;
//     }
//     ~Test () { if (file) delete file; }

//     Token next () {
// 	string res = readln (index);
// 	index++;
// 	loc.column++;
// 	cout << "index: " << index << endl;
// 	return Token (res, loc);
//     }

//     string readln (unsigned int offset) {
// 	file->seekg (offset);
// 	string res = "";
// 	getline (*file, res);
// 	if (res.size() == 0) {
// 	    getline (*file, res);
// 	    index++;
// 	    loc.line++;
// 	    loc.column = 0;
// 	}
// 	file->seekg (0);
// 	return res;
//     }

//     ifstream * file;
//     unsigned int index;
//     location_t loc;
// };

int main() {

    Lexer lex ("test.nx");
    lex.setKeys ({" ", "=", ";"});
    int i = 0; 
    while (!lex.isEof() && i++ < 10) {
    	Token t = lex.next();
    	if (i < 4) cout << t.to_string() << endl;
    }

    // Test t("test.nx");
    // Token r = t.next ();
    // while (r.value.size() > 0) {
    // 	cout << r.to_string() << endl;
    // 	r = t.next ();
    // }

    return 0;
}
