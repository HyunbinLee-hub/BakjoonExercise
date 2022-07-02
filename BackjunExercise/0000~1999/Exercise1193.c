#include <stdio.h>

int main(void)
{
	int i = 0, j = 0;
	int num, sum;

	scanf("%d", &num);
	sum = 0;
	while (1) {
		sum += i++;
		j = num - sum;
		if (j >= 0 && j <= i) {
			break;
		}
	}
	
	if (i % 2 == 1)
		printf("%d/%d \n", (i + 1) - j, j);
	else
		printf("%d/%d \n", j, (i + 1) - j);
	return 0;
}