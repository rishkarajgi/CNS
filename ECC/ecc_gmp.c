#include <stdio.h>
#include <gmp.h>
void point_doubling(mpz_t xP, mpz_t yP, mpz_t a);
void point_add(mpz_t xP, mpz_t yP, mpz_t xQ, mpz_t yQ);
void point_add(mpz_t xP, mpz_t yP, mpz_t xQ, mpz_t yQ){
  mpz_t lambda_num, lambda_denom,pow,xR,yR,lambda,lambda_sq,temp;
  mpz_init(lambda_num);
  mpz_init(temp);
  mpz_init(pow);
  mpz_init(lambda_sq);
  mpz_init(lambda);
  mpz_init(lambda_denom);
  mpz_init(xR);
  mpz_init(yR);

  mpz_sub(lambda_num,yQ,yP);
  mpz_sub(lambda_denom,xQ,xP);
  mpz_cdiv_q(lambda, lambda_num, lambda_denom);

  mpz_set_ui (pow, 2);
  mpz_pow_ui(lambda_sq,lambda,2);
  mpz_add(temp,xP,xQ);
  mpz_sub(xR,lambda_sq,temp);
  mpz_sub(temp,xP,xR);
  mpz_mul(lambda_sq,lambda,temp);
  mpz_sub(yR,lambda_sq,yP);
  gmp_printf ("The value of xR = %Zd\n", xR);
  gmp_printf ("The value of yR = %Zd\n", yR);
}
void point_doubling(mpz_t xP, mpz_t yP, mpz_t a){
  mpz_t lambda_num, lambda_denom,pow,xR,yR,lambda,lambda_sq,temp,temp1;
  mpz_init(lambda_num);
  mpz_init(temp1);
  mpz_init(temp);
  mpz_init(pow);
  mpz_init(lambda_sq);
  mpz_init(lambda);
  mpz_init(lambda_denom);
  mpz_init(xR);
  mpz_init(yR);

  //for calculating lambda
  mpz_pow_ui(lambda_sq,lambda,2);
  mpz_pow_ui(temp,xP,2);
  mpz_mul_ui(temp1,temp,3);
  mpz_add(lambda_num,temp1,a);
  mpz_mul_ui(lambda_denom,yP,2);
  mpz_cdiv_q(lambda, lambda_num, lambda_denom);

  mpz_mul_ui(temp,xP,2);
  mpz_sub(xR,lambda_sq,temp);

  gmp_printf ("The value of xR = %Zd\n", xR);

  mpz_sub(temp,xP,xR);
  mpz_mul(temp1,lambda,temp);
  mpz_sub(yR,temp1,yP);

  gmp_printf ("The value of yR = %Zd\n", yR);






}
int main(){
  mpz_t xP,yP,xQ,yQ,a;
  mpz_init(xP);
  mpz_init(a);
  mpz_init(yP);
  mpz_init(xQ);
  mpz_init(yQ);
  printf("xP?\n");
  gmp_scanf ("%Zd",xP);
  printf("yP?\n");
  gmp_scanf ("%Zd",yP);
  printf("xQ?\n");
  gmp_scanf ("%Zd",xQ);
  printf("yQ?\n");
  gmp_scanf ("%Zd",yQ);
  printf("a?\n");
  gmp_scanf ("%Zd",a);
  printf("POINT ADDITION:\n");
  point_add(xP,yP,xQ,yQ);
  printf("POINT DOUBLING:\n");
  point_doubling(xP,yP,a);
  return 0;
}