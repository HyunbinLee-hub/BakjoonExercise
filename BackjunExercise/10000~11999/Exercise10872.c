#include <stdio.h>

int factorial(int num) {
	if (num == 0)
		return 1;
	else
		return num *= factorial(num - 1);
}


int main(void)
{
	int num, res;
	scanf("%d", &num);
	if (num >= 0 && num < 13) {
		res = factorial(num);
		printf("%d \n", res);
	}

	return 0;
}