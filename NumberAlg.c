#include "NumberAlg.h"
#include <stdlib.h>
#include <math.h>
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

i64 modular_linear_equation_solver(ui64 a, ui64 b, ui64 n, i64** ret)
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

ui64 modular_exponentiation(ui64 a, ui64 b, ui64 n)
{
	ui64  d = 1,tem=1;
	int i = 63;
	for (; i >= 0; i--)
	{
		if (b & (tem << i))
			break;
	}
	for (; i >= 0; i--)
	{
		d = (d * d) % n;
		if (b & (tem << i))
		{
			d = (d * a) % n;
		}
	}
	return d;
}

int pseudoprime(ui64 n)
{
	if (modular_exponentiation(2, n - 1, n) != 1)
		return 0;
	return 1;
}


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
}

ui64 rand64(ui64 minv,ui64 maxv)
{
	ui64 ret = 0;
	short* p = (short*)&ret;
	p[0] = rand()%0x7fff;
	p[1] = rand() % 0x7fff;
	p[2] = rand() % 0x7fff;
	p[3] = rand() % 0x7fff;
	return ret % (maxv - minv)+ minv;

}
int miller_rabin(ui64 n, ui64 s)
{
	if (n == 2)
		return 1;
	if (n < 2 || !(n & 1))
		return 0;
	srand((unsigned)time(NULL));
	for (ui64 j = 1; j <= s; j++)
	{
		ui64 a = rand64(1,n-1);
		if (witness(a, n))
			return 0;
	}
	return 1;
}
