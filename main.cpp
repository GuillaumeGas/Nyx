#include <iostream>

#include "Compilo.hpp"

using namespace std;

int main(int argc, char** argv) {
  
  Compilo c;
  c.compile(argv[1]);
  c.print_tokens();
  
  return 0;
}
