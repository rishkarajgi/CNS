dh
==

*Only for demonstration purposes.*

Interactive Diffie-Hellman key exchange with GNU MP

Compile it:

> g++ main.cpp -odh -O3 -Wall -lgmp -lgmpxx

Use it:

> ./dh

Generate suitable primes
------------------------

> g++ prime.cpp -oprime -O3 -Wall -std=c++0x -lgmp -lgmpxx

> ./prime 500

... to create a prime with 500 decimal digits.
