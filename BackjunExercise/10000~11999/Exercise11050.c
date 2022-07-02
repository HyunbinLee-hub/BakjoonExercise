#include <stdio.h>

int BinomialCoefficient(int num1, int num2)
{
	int res1;
	int mul = 1, div = 1;

	if (num2 <= num1 / 2)
		res1 = num2;
	else
		res1 = num1 - num2;

	for (int i = 0; i < res1; i++) {
		mul *= num1 - i;
		div *= (i + 1);
	}
	return mul / div;
}

int main(void)
{
	int num1, num2;
	int flag = 0, res = 0;

	while (flag != 1) {
		scanf("%d%d", &num1, &num2);
		if (num1 < 1 || num1 > 10)
			continue;
		if (num2 < 0 || num2 > num1)
			continue;
		flag = 1;
	}

	res = BinomialCoefficient(num1, num2);
	printf("%d\n", res);
	return 0;
}