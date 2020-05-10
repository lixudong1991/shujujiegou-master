#ifndef NUMBERALG_H_H_
#define NUMBERALG_H_H_
#include "gmp.h"
typedef	unsigned long long ui64;
typedef	long long i64;

/*
	欧几里得算法求a,b的最大公约数gcd(a,b)
	欧几里得定理 gcd(a,b)=gcd(b,a mod b);
*/
ui64 gcd(ui64 a, ui64 b);

typedef struct GcdResult
{
	mpz_t d;
	mpz_t x, y;
}GcdResult;
/*
	欧几里得算法求a,b的最大公约数gcd(a,b),和参数x,y使a*x+b*y=gcd(a,b)
	参数a>参数b
*/
void gcd_Result(mpz_t a, mpz_t b, GcdResult* res);

/*
	求解模线性方程，a*x mod n =b; 的所有x的值，返回第m个x值 a<n,x<n;x的值在ret中
*/
int modular_linear_equation_solver(mpz_t a, mpz_t b, mpz_t n, mpz_t* ret,int m);

/*
	反复平方法求 a^b mod n,a>=0,b>=0,n>0;
*/
void modular_exponentiation(mpz_t* a, mpz_t* b, mpz_t* n, mpz_t* d);

/*
伪素数测试
*/
int pseudoprime(ui64 n);

/*
	MILLE-RABIN素数测试 n待测试的数，s测试的次数
*/
int miller_rabin(mpz_t* n, ui64 s);


typedef struct RsaKey
{
	mpz_t val;
	mpz_t n;
}RsaKey;

#define MAX_BIT_INDEX 1023
int createKey(RsaKey* prikey, RsaKey* pubkey);
#endif // !NUMBERALG_H_H_

