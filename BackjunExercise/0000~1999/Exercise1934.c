#include <stdio.h>

int main(void)
{
	int cnt;
	int a, b, num;

	scanf("%d", &cnt);
	for (int i = 0; i < cnt; i++)
	{
		int fac = 1;
		int res = 1;
		scanf("%d%d", &a, &b);
		num = (a > b) ? b : a;
		for (int j = 2; j <= num; j++) {
			while (a % j == 0 && b % j == 0) {
				fac *= j;
				a /= j;
				b /= j;
			}
		}

		if (a == b) res = fac*a;
		else res = fac * a * b;
		printf("%d\n", res);
	}
	return 0;
}