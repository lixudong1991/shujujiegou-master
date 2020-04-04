#include "NumberAlg.h"

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