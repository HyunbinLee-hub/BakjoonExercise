#include <stdio.h>

int main(void)
{
	long a, b, c;
	long amount = 1;

	scanf("%d %d %d", &a, &b, &c);
	if (b >= c) {
		printf("-1");
	}
	else {
		amount = a / (c - b) + 1;
		printf("%d \n", amount);
	}
	return 0;
}