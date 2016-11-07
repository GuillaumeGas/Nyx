#include <iostream>

#include "compilo/Compilo.hpp"

using namespace std;

int main(int argc, char** argv) {

  if(argc > 1) {
    bob::Compilo c(argv[1]);
    c.compile();
    cout << " -- AST -- " << endl;
    c.print_ast();
    cout << " -- FIN AST -- " << endl;
  } else {
    cout << "[Error] no source file." << endl;
  }

  return 0;
}
