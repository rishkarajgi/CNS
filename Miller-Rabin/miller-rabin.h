
#ifndef INC_MILLER_RABIN_H
#define INC_MILLER_RABIN_H

#include <stdint.h>

/*
 * Accuracy parameter `k´ of the Miller-Rabin algorithm.
 *
 */
static const int DEFAULT_ACCURACY = 5;

/*
 * The Miller-Rabin probabilistic primality test.
 *
 * Returns true if ``n´´ is PROBABLY prime, false if it's composite.
 * The parameter ``k´´ is the accuracy.
 *
 * The running time should be somewhere around O(k log_3 n).
 *
 */
bool isprime(uint64_t n, int accuracy = DEFAULT_ACCURACY);

void setrand(int (*rand_function)(void), const int rand_max);

#endif // INC_MILLER_RABIN_H
