#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int num;
	int i, cnt;
	int *arr = (int *)calloc(300000, sizeof(int));
	
	while (1) {
		scanf("%d", &num);
		if (num == 0)
			break;
		else if (num < 1 || num > 123456)
			continue;
		else {
			cnt = 0;
			arr[1] = 1;
			for (i = 2; i <= 2 * num; i++) {
				for (int j = 2; i*j <= 2 * num; j++)
					arr[i*j] = 1;
			}
			for (i = 2*num; i > num; i--)
				if (arr[i] == 0) cnt++;
			printf("%d \n", cnt);
		}
	}

	free(arr);
	return 0;
}