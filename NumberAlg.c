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