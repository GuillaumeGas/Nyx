void print_i (int val) {
    $printi (val, 0);
}

int main () {
    int a = 0;
    for (i in 0 .. 10) {
	while:test (true) {
		a = a + 1;
		if (a > 10) {
		    break test;
		}
	    }
    }
    for:f (a in 20 .. 0) {
	print_i (a);
    }
    return 0;
}
