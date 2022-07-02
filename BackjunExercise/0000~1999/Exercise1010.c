#include <stdio.h>

long long BinomialCoefficient(int num1, int num2)
{
	int thres;
	long long mul = 1, div = 1;
	int res = 1;

	if (num2 <= num1 / 2)
		thres = num2;
	else
		thres = num1 - num2;
	for (int i = 0; i < thres; i++)
	{
		mul *= (num1-i);
		div *= (i+1);
	}
	res = mul / div;
	return res;
}

int main(void)
{
	int cnt;
	int n, m;
	long long res;

	scanf("%d", &cnt);
	for (int i = 0; i < cnt; i++)
	{
		scanf("%d%d", &n, &m);
		res = BinomialCoefficient(m, n);
		printf("%lld\n", res);
	}
	return 0;
}