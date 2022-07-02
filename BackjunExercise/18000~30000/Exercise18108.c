#include <stdio.h>

int main(void)
{
	int budYear, res;

	res = 0;
	while (1) {
		scanf("%d", &budYear);
		if (budYear >= 1000 && budYear <= 3000)	res = 1;
		if (res == 1) break;
	}

	printf("%d \n", budYear - 543);
	return 0;
}