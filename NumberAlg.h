#ifndef NUMBERALG_H_H_
#define NUMBERALG_H_H_

typedef	unsigned long long ui64;
typedef	long long i64;

/*
	欧几里得算法求a,b的最大公约数gcd(a,b)
	欧几里得定理 gcd(a,b)=gcd(b,a mod b);
*/
ui64 gcd(ui64 a, ui64 b);

typedef struct GcdResult
{
	ui64 d;
	i64 x, y;
}GcdResult;
/*
	欧几里得算法求a,b的最大公约数gcd(a,b),和参数x,y使a*x+b*y=gcd(a,b)
	参数a>参数b
*/
void gcd_Result(ui64 a, ui64 b, GcdResult *res);

#endif // !NUMBERALG_H_H_

