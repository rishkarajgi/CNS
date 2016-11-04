#include <iostream>
#include <gmpxx.h>
#include <random>
 
using namespace std;
 
bool numeric(const char* x) {
	for (; *x; x++) {
		if (!(*x >= '0' && *x <= '9')) {
			return false;
		}
	}
 
	return true;
}
 
int main(int argc, char** argv) {
	uint64_t LEN = 0;
 
	if (argc == 2) {
		if (numeric(argv[1])) {
			LEN = atoll(argv[1]);
		}
		else {
			cout << "This is not a valid length specification." << endl;
			cout << "Example:\t" << argv[0] << " 100" << endl;
			cout << "\tto generate a prime number with at least 100 decimal digits." << endl;
 
			return 2;
		}
	}
	else {
		cout << "Usage:\t" << argv[0] << " 100" << endl;
		cout << "\tto generate a prime number with at least 100 decimal digits." << endl;
 
		return 1;
	}
 
	mpz_t a, b;
	mpz_init(a);
	mpz_init(b);
	char rndstr[LEN+1];
 
	random_device rd;
	uniform_int_distribution<> dis(1,9), dis2(0,9);
 
	rndstr[0] = dis(rd)+'0';
 
	for (unsigned i = 0; i < LEN-1; i++) {
		rndstr[i+1] = dis2(rd)+'0';
	}
 
	rndstr[LEN] = 0;
 
	mpz_set_str(a,rndstr,10);
 
	mpz_nextprime(b,a);
 
	gmp_printf("%Zd\n", b);
 
	mpz_clear(a);
	mpz_clear(b);
}
