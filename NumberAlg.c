#include "NumberAlg.h"
#include <stdlib.h>
#include <time.h>

ui64 gcd(ui64 a, ui64 b)
{
	ui64 tmp = 0;
	if (b > a)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	while (b)
	{
		tmp = b;
		b = a % b;
		a = tmp;	
	}
	return a;
}

void gcd_Result(ui64 a, ui64 b, GcdResult* res)
{

	if (b == 0)
	{
		res->d = a;
		res->x = 1;
		res->y = 0;
	}
	else
	{
	    gcd_Result(b, a % b,res);
		i64 x1 = res->x, y1 = res->y;
		res->x = y1;
		res->y = x1 - a / b * y1;
	}
}

ui64 modular_linear_equation_solver(ui64 a, ui64 b, ui64 n, i64** ret)
{
	GcdResult res;
	gcd_Result(n, a, &res);
	if (!(b % res.d))
	{
		if (res.y < 0)
			res.y += n;
		i64 x0 = (res.y * (b / res.d)) % n;
		(*ret) = malloc(res.d * sizeof(i64));
		for (ui64 i = 0; i < res.d; i++)
			(*ret)[i] = (x0 + i * (n / res.d)) % n;
		return res.d;
	}
	else
	return 0;
}

void modular_exponentiation(mpz_t* a, mpz_t* b, mpz_t* n, mpz_t* d)
{
	mpz_init_set_ui(*d, 1);
	int i = MAX_BIT_INDEX;
	for (; i >= 0; i--)
	{
		if (mpz_tstbit(*b, i))
			break;
	}
	for (; i >= 0; i--)
	{
		mpz_mul(*d, *d, *d);
		mpz_mod(*d, *d, *n);
		if (mpz_tstbit(*b, i))
		{
			// d = (d * a) % n;
			mpz_mul(*d, *d, *a);
			mpz_mod(*d, *d, *n);
		}
	}
}


int pseudoprime(ui64 n)
{
/*	if (modular_exponentiation(2, n - 1, n) != 1)
		return 0;*/
	return 1;
}

/*
static int witness(ui64 a, ui64 n)
{
	ui64 t = 1, u = (n - 1) >> 1;
	while (!(u&1))
	{
		u >>= 1;
		t++;
	}
	ui64 x = modular_exponentiation(a, u, n),y=1;
	for (ui64 i = 1; i <= t; i++)
	{
		y = (x * x) % n;
		if ((y == 1) && (x != 1) && (x != n - 1))
			return 1;
		x = y;
	}
	if (y != 1)
		return 1;
	return 0;
}*/

static int witness(mpz_t* a, mpz_t* n)
{
	ui64 t = 1, ret = 0;
	mpz_t u, x, y, tem;
	mpz_init(u);
	mpz_init(x);
	mpz_init(y);
	mpz_init(tem);
	mpz_sub_ui(u, *n, 1);
	mpz_div_2exp(u, u, 1);
	while (!mpz_tstbit(u, 0))
	{
		mpz_div_2exp(u, u, 1);
		t++;
	}
	modular_exponentiation(a, &u, n, &x);
	mpz_init_set_ui(y, 1);
	mpz_sub_ui(tem, *n, 1);
	for (ui64 i = 1; i <= t; i++)
	{
		mpz_mul(y, x, x);
		mpz_mod(y, y, *n);
		if (mpz_cmp_ui(y, 1) == 0 && (mpz_cmp_ui(x, 1) != 0) && (mpz_cmp(x, tem) != 0)) {
			mpz_clear(u);
			mpz_clear(x);
			mpz_clear(y);
			mpz_clear(tem);
			return 1;
		}

		mpz_set(x, y);
	}
	if (mpz_cmp_ui(y, 1) != 0)
		ret = 1;
	mpz_clear(u);
	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(tem);
	return ret;
}


int miller_rabin(mpz_t* n, ui64 s)
{
	if (mpz_cmp_ui(*n, 2) == 0)
		return 1;
	if (mpz_cmp_ui(*n, 2) < 0 || !mpz_tstbit(*n, 0))
		return 0;
	clock_t time = clock();
	int ret = 1;
	gmp_randstate_t grt;
	gmp_randinit_default(grt);
	gmp_randseed_ui(grt, time);
	mpz_t key, maxr;
	mpz_init(key);
	mpz_init(maxr);
	mpz_sub_ui(maxr, *n, 1);
	for (ui64 j = 1; j <= s; j++)
	{
		mpz_urandomm(key, grt, maxr);
		mpz_add_ui(key, key, 1);
		if (witness(&key, n))
			ret = 0;
	}
	mpz_clear(key);
	mpz_clear(maxr);
	return ret;
}