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

/*
	求解模线性方程，a*x mod n =b; 的所有x的值，返回的数组需要释放 a<n,x<n;x的值在ret中
*/
ui64 modular_linear_equation_solver(ui64 a, ui64 b, ui64 n,i64** ret);

/*
	反复平方法求 a^b mod n,a>=0,b>=0,n>0;
*/
ui64 modular_exponentiation(ui64 a, ui64 b, ui64 n);

/*
伪素数测试
*/
int pseudoprime(ui64 n);

/*
	MILLE-RABIN素数测试 n待测试的数，s测试的次数
*/
int miller_rabin(ui64 n, ui64 s);

#endif // !NUMBERALG_H_H_

