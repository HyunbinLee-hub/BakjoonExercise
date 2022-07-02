#include <stdio.h>

int main(void)
{
	int a, b;
	int min;
	int mes = 1;
	scanf("%d%d", &a, &b);
	min = (a > b) ? b : a;
	for (int i = 2; i <= min; i++) {
		while (a % i == 0 && b % i == 0) {
			mes *= i;
			a /= i;
			b /= i;
		}
	}
	if (a != b)
		printf("%d\n%d\n", mes, mes*a*b);
	else
		printf("%d\n%d\n", mes, mes*a);
	return 0;
}