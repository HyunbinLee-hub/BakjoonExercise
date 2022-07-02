#include <stdio.h>

int main(void)
{
	int m, n;
	int sum = 0, min, flag;
	int i, j;

	scanf("%d", &m);
	scanf("%d", &n);

	min = n;

	for (i = m; i <= n; i++) {
		flag = 0;
		if (i == 1)
			continue;
		for (j = 2; j < i; j++) {
			if (i % j == 0) {
				flag = 1;
			}
		}
		if (flag == 0) {
			if (sum == 0) min = i;
			sum += i;
		}
	}

	if (sum != 0) {
		printf("%d \n", sum);
		printf("%d \n", min);
	}
	else
		printf("-1 \n");
	return 0;
}