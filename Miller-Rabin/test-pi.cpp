#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "miller-rabin.h"

static int pi(int n)
{
  int r=0, m=2;

  while ( m < n )
    if ( isprime(m++) ) ++r;

  return r;
}

static uint64_t randcalls = 0;
int myrand()
{
  ++randcalls;
  return rand();
}

int main()
{
  srand(time(0));
  setrand(myrand, RAND_MAX);

  printf(
    "Calculating pi(n) by using the Miller-Rabin primality test.\n"
    "\n"
    "While this is a SLOW way of computing pi(n), we use it to test\n"
    "the accuracy parameter `k´.\n"
    "\n"
    "Note that since this is a probabilistic algorithm, each run can\n"
    "produce different results.  That is why you might see incorrect\n"
    "results below, from time to time.\n"
    "\n"
    "Written by Christian Stigen Larsen, http://csl.sublevel3.org\n"
    "\n"
    "For this run, k = %d\n\n", DEFAULT_ACCURACY);

  int expected[] = {0, 4, 25, 168, 1229, 9592, 78498, 664579};

  for ( int n=1, e=0; n<=10000000; n*=10, ++e ) {
    int primes = pi(n);
    printf("There are %d primes less than %d", primes, n);

    if ( primes == expected[e] ) printf("\n");
    else printf(" --- FAIL, expecteded %d\n", expected[e]);
  }

  printf("\nThe randomization function was called %Lu times\n", randcalls);
  return 0;
}
