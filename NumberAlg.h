#ifndef NUMBERALG_H_H_
#define NUMBERALG_H_H_

typedef	unsigned long long ui64;
typedef	long long i64;

/*
	ŷ������㷨��a,b�����Լ��gcd(a,b)
	ŷ����ö��� gcd(a,b)=gcd(b,a mod b);
*/
ui64 gcd(ui64 a, ui64 b);

typedef struct GcdResult
{
	ui64 d;
	i64 x, y;
}GcdResult;
/*
	ŷ������㷨��a,b�����Լ��gcd(a,b),�Ͳ���x,yʹa*x+b*y=gcd(a,b)
	����a>����b
*/
void gcd_Result(ui64 a, ui64 b, GcdResult *res);

#endif // !NUMBERALG_H_H_

