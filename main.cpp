#include <iostream>

#include "compilo/Compilo.hpp"
#include "global/Global.hpp"

using namespace std;

int main(int argc, char** argv) {

	if (argc > 1) {
		nyx::Compilo c(argv[1]);
		c.compile();
	}
	else {
		cout << "[Error] no source file." << endl;
	}

	return 0;
}
