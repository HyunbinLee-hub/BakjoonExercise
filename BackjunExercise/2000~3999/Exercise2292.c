#include <stdio.h>

int main(void)
{
	int num;
	int diff = 0;
	int sum = 0;
	int count = 1;

	scanf("%d", &num);
	while (1) {
		if (num - 1 <= sum) break;
		diff = 6 * count;
		sum += diff;
		++count;
	}
	printf("%d \n", count);
	return 0;
}