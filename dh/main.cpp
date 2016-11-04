#include <iostream>
#include <gmpxx.h>

using namespace std;

mpz_class powm(mpz_class base, mpz_class exponent, mpz_class mod) {
	mpz_class r;
	
	mpz_powm(r.get_mpz_t(),base.get_mpz_t(),exponent.get_mpz_t(),mod.get_mpz_t());
	
	return r;
}

int main() {
	mpz_class p,g,a,B;
	
	cout << "p: prime number (public)" << endl;
	cout << "p = ";
	cin >> p;
	
	cout << "g: base (public)" << endl;
	cout << "g = ";
	cin >> g;

	cout << "a: integer between 1 and p-2 (secret)" << endl;
	cout << "a = ";
	cin >> a;
	
	mpz_class A = powm(g,a,p); // A = g^a mod p
	
	cout << "\nA: your partner should enter this number as 'B'" << endl;
	cout << "A = " << A << endl;
	
	cout << "\nB: your partner's A" << endl;
	cout << "B = ";
	cin >> B;
	
	mpz_class s = powm(B,a,p); // s = B^a mod p
	
	cout << "\ns: Shared secret" << endl;
	cout << "s = " << s << endl;
}
