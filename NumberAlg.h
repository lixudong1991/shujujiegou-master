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

/*
	���ģ���Է��̣�a*x mod n =b; ������x��ֵ�����ص�������Ҫ�ͷ� a<n,x<n;x��ֵ��ret��
*/
ui64 modular_linear_equation_solver(ui64 a, ui64 b, ui64 n,i64** ret);

/*
	����ƽ������ a^b mod n,a>=0,b>=0,n>0;
*/
ui64 modular_exponentiation(ui64 a, ui64 b, ui64 n);

/*
α��������
*/
int pseudoprime(ui64 n);

/*
	MILLE-RABIN�������� n�����Ե�����s���ԵĴ���
*/
int miller_rabin(ui64 n, ui64 s);

#endif // !NUMBERALG_H_H_

