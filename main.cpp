#include <iostream>

#include "compilo/Compilo.hpp"

using namespace std;

int main(int argc, char** argv) {

  if(argc > 1) {
    bob::Compilo c(argv[1]);
    c.compile();
    c.print_tokens();
    c.print_ast();
  } else {
    cout << "[Error] no source file." << endl;
  }

  return 0;
}
