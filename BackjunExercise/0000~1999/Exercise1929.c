#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	int m, n;
	int *arr = (int *)calloc(1000001, sizeof(int));
	arr[1] = 1;

	scanf("%d%d", &m, &n);
	
	if (1 <= m && m <= n) {
		for (int i = 2; i <= n; i++) {
			for (int j = 2; i*j <= n; j++) {
				arr[i*j] = 1;
			}
		}

		for (int i = m; i < n + 1; i++) {
			if (arr[i] == 0)
				printf("%d \n", i);
		}
	}
	free(arr);
	return 0;
}