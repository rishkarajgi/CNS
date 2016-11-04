#include <stdio.h>

#include <gmp.h>
#include <mpfr.h>

int main(void)
{
  unsigned int i;
  mpfr_t s, t, u;

  mpfr_init2(t, 200);
  mpfr_set_d(t, 1.0, GMP_RNDD);
  mpfr_init2(s, 200);
  mpfr_set_d(s, 1.0, GMP_RNDD);
  mpfr_init2(u, 200);
  for (i = 1; i <= 100; i++)
    {
      mpfr_mul_ui(t, t, i, GMP_RNDU);
      mpfr_set_d(u, 1.0, GMP_RNDD);
      mpfr_div(u, u, t, GMP_RNDD);
      mpfr_add(s, s, u, GMP_RNDD);
    }
  printf("Sum is ");
  mpfr_out_str(stdout, 10, 0, s, GMP_RNDD);
  putchar('\n');
  mpfr_clear(s);
  mpfr_clear(t);
  mpfr_clear(u);
  return 0;
} 