#ifndef NUMBERALG_H_H_
#define NUMBERALG_H_H_

typedef	unsigned long long ui64;

/*
	欧几里得算法求a,b的最大公约数
	欧几里得定理 gcd(a,b)=gcd(b,a mod b);
*/
ui64 gcd(ui64 a, ui64 b);
#endif // !NUMBERALG_H_H_

