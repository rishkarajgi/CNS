#include <stdio.h>
#include <gmp.h>

void gcd(mpz_t d, mpz_t x, mpz_t y, mpz_t a, mpz_t b);

int main(int argc, char *argv[])
{
  mpz_t d, x, y, a, b;
  mpz_init(d); mpz_init(x); mpz_init(y); mpz_init(a); mpz_init(b);

  if (argc != 3)
    {
      printf("SPECIFY TWO INTEGERS!\n");
      exit(1);
    }
  else
    {
      mpz_set_str(a,argv[1],10);
      mpz_set_str(b,argv[2],10);
    }

  gcd(d,x,y,a,b);

  printf("       a = ");
  mpz_out_str (stdout, 10, a);
  printf (",\n");
  printf("       b = ");
  mpz_out_str (stdout, 10, b);
  printf (",\n");
  printf("gcd(a,b) = ");
  mpz_out_str (stdout, 10, d);
  printf (".\n");
  printf("Furthermore, gcd(a,b) = ax+by with\n");
  printf("       x = ");
  mpz_out_str (stdout, 10, x);
  printf (",\n");
  printf("       y = ");
  mpz_out_str (stdout, 10, y);
  printf (".\n");
 

  mpz_clear(d); mpz_clear(x); mpz_clear(y); mpz_clear(a); mpz_clear(b);
  return 0;
}

void gcd(mpz_t d0, mpz_t x0, mpz_t y0, mpz_t a, mpz_t b)
{
  mpz_t d1, d2;
  mpz_t x1, x2;
  mpz_t y1, y2;
  mpz_t q;

  mpz_init(d1); mpz_init(d2);
  mpz_init(x1); mpz_init(x2);
  mpz_init(y1); mpz_init(y2);
  mpz_init(q);
  
  if ( (mpz_sgn(a)==0) && (mpz_sgn(b)==0) )
    {
      printf("ERROR: TRIED TO COMPUTE gcd(0,0)\n");
      exit(1);
    }

  if (mpz_sgn(a) < 0)
    mpz_neg (a, a);

  if (mpz_sgn(b) < 0)
    mpz_neg (b, b);

  if (mpz_cmp (a, b) < 0)
    mpz_swap (a, b);

  mpz_set (d0, a); mpz_set_ui (x0, 1); mpz_set_ui (y0, 0);
  mpz_set (d1, b); mpz_set_ui (x1, 0); mpz_set_ui (y1, 1);

  while(mpz_sgn(d1) != 0)
    {
      mpz_fdiv_qr (q, d2, d0, d1);

      mpz_mul (x2,  q, x1);
      mpz_sub (x2, x0, x2);

      mpz_mul (y2,  q, y1);
      mpz_sub (y2, y0, y2);

      mpz_set(d0, d1); mpz_set(x0, x1); mpz_set(y0, y1);
      mpz_set(d1, d2); mpz_set(x1, x2); mpz_set(y1, y2);
    }

  mpz_clear(d1); mpz_clear(d2);
  mpz_clear(x1); mpz_clear(x2);
  mpz_clear(y1); mpz_clear(y2);
  mpz_clear(q);
}