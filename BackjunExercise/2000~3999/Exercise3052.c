#include <stdio.h>

int main(void)
{
	int num[10];
	int rmd[10];
	int i, j;
	int count = 10;

	for (i = 0; i < 10; i++) {
		scanf("%d", &num[i]);
		rmd[i] = num[i] % 42;
	}

	for (i = 0; i < sizeof(rmd) / sizeof(int); i++) {
		for (j = i + 1; j < sizeof(rmd) / sizeof(int); j++)
			if (i != j && rmd[i] == rmd[j]) {
				count--;
				break;
			}
	}
	printf("%d \n", count);
	return 0;
}