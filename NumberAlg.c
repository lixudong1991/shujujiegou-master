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

void gcd_Result(mpz_t a, mpz_t b, GcdResult* res)
{
	mpz_t c, d, e, x1, y1;
	mpz_init(c);
	mpz_init(d);
	mpz_init(e);
	mpz_init(x1);
	mpz_init(y1);
	mpz_set(d, b);
	if (mpz_cmp_ui(d, 0) == 0)
	{
		// res->d = a;
		mpz_set(res->d, a);
		// res->x = 1;
		mpz_set_ui(res->x, 1);
		//res->y = 0;
		mpz_set_ui(res->y, 0);
	}
	else
	{
		mpz_mod(e, a, b);
		gcd_Result(d, e, res);
		mpz_set(x1, res->x);
		mpz_set(y1, res->y);
		mpz_set(res->x, y1);
		mpz_div(c, a, b);
		mpz_mul(c, c, y1);
		mpz_sub(res->y, x1, c);
	}
	mpz_clear(x1);
	mpz_clear(y1);
	mpz_clear(e);
	mpz_clear(c);
	mpz_clear(d);
}
int modular_linear_equation_solver(mpz_t a, mpz_t b, mpz_t n, mpz_t* ret,int m)
{
	GcdResult res;
	mpz_init_set_ui(res.x, 0);
	mpz_init_set_ui(res.y, 0);
	mpz_init_set_ui(res.d, 0);
	gcd_Result(n, a, &res);
	mpz_t tmp,x0;
	int r= 0;
	mpz_init_set_ui(tmp, 0);
	mpz_init_set_ui(x0, 0);
	mpz_mod(tmp, b, res.d);
	if (mpz_cmp_ui(tmp, 0) == 0)
	{
		printf("ÄæÔª=%s\n", mpz_get_str(NULL,16,res.y));
		if (mpz_cmp_ui(res.y, 0) < 0)
			mpz_add(res.y, res.y, n);
		printf("ÄæÔª=%s\n", mpz_get_str(NULL, 16, res.y));
		mpz_div(x0, b, res.d);
		mpz_mul(x0, x0, res.y);
		mpz_mod(x0, x0, n);
		mpz_div(tmp, n, res.d);
		mpz_mul_ui(tmp, tmp, m);
		mpz_add(x0, x0, tmp);
		mpz_mod(*ret, x0, n);
		r= 1;
	}
	else
		r= 0;

	mpz_clear(tmp);
	mpz_clear(x0);
	mpz_clear(res.x);
	mpz_clear(res.y);
	mpz_clear(res.d);
	return r;
	/*
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
	return 0;*/
	
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

int createKey(RsaKey* prikey, RsaKey* pubkey)
{
	clock_t time = clock();
	int ret = 0;
	gmp_randstate_t grt;
	gmp_randinit_default(grt);
	gmp_randseed_ui(grt, time);
	mpz_t p,q,base,n,maxv,nn,e,b,d;
	mpz_init_set_ui(p,0);
	mpz_init_set_ui(q, 0);
	mpz_init_set_ui(base, 1);
	mpz_init_set_ui(n, 0);
	mpz_init_set_ui(maxv, 1);
	mpz_init_set_ui(nn, 0);
	mpz_init_set_ui(e, 3);
	mpz_init_set_ui(d, 1);
	mpz_init_set_ui(b, 1);
	mpz_mul_2exp(base, base, MAX_BIT_INDEX);
	mpz_mul_2exp(maxv, maxv, MAX_BIT_INDEX+1);
k:	mpz_urandomm(p, grt, base);
	if (mpz_even_p(p))
		mpz_add_ui(p, p, 1);
	if (mpz_cmp(p, base) < 0)
		mpz_add(p, p, base);
	while (!miller_rabin(&p, 10))
	{
		mpz_add_ui(p, p, 2);
		if (mpz_cmp(p, maxv) >= 0)
			goto k;
	}
k1:	mpz_urandomm(q, grt, base);
	if (mpz_even_p(q))
		mpz_add_ui(q, q, 1);
	if (mpz_cmp(q, base) < 0)
		mpz_add(q, q, base);
	while (!miller_rabin(&q, 10))
	{
		mpz_add_ui(q, q, 2);
		if (mpz_cmp(q, maxv) >= 0)
			goto k1;
	}
	printf("p = %s\n", mpz_get_str(NULL, 16, p));
	printf("q = %s\n", mpz_get_str(NULL, 16, q));
	mpz_mul(n, p, q);
	//printf("n = %s\n", mpz_get_str(NULL, 16, n));
	mpz_sub_ui(p, p, 1);
	mpz_sub_ui(q, q, 1);
	mpz_mul(nn, p, q);
	printf("nn = %s\n", mpz_get_str(NULL, 16, nn));
	mpz_add_ui(p, p, 1);
	mpz_add_ui(q, q, 1);

	while (!modular_linear_equation_solver(e, b, nn, &d, 0))
	{
		mpz_add_ui(e, e, 2);
	}	
	mpz_set(pubkey->val, e);
	mpz_set(pubkey->n, n);
	mpz_set(prikey->val, d);
	mpz_set(prikey->n, n);
	ret = 1;
	mpz_clear(p);
	mpz_clear(q);
	mpz_clear(base);
	mpz_clear(n);
	mpz_clear(maxv);
	mpz_clear(nn);
	mpz_clear(e);
	mpz_clear(b);
	mpz_clear(d);
	return ret;
}
