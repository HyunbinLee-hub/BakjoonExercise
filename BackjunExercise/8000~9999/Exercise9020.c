#include <stdio.h>

int main(void)
{
	int cnt, num;
	int arr[10001] = { 0, };
	int i, j;

	for (j = 2; j < 10001/j; j++) {
		if (!arr[j]) {
			for (i = j * j; i < 10001; i += j) {
				if (i % j == 0) arr[i] = 1;
			}
		}
	}

	scanf("%d", &cnt);
	while (cnt--) 
	{
		scanf("%d", &num);
		for (i = num / 2; i > 1; i--) {
			if (arr[i] == 1) continue;
			for (j = num / 2; j <= num; j++) {
				if (arr[j] == 1) continue;
				if (i + j == num) break;
			}
			if (i + j == num) break;
		}
		printf("%d %d \n", i, j);
	}
	return 0;
}