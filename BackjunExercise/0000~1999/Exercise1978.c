#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	int arrCnt;
	int *arr, i;
	int cnt = 0;

	scanf("%d", &arrCnt);
	arr = (int *)calloc(arrCnt, sizeof(int));
	for (int i = 0; i < arrCnt; i++) {
		scanf("%d", &arr[i]);
	}

	cnt = arrCnt;
	for (i = 0; i < arrCnt; i++) {
		if (arr[i] == 1) {
			cnt -= 1;
		}
		for (int j = 2; j < arr[i]; j++) {
			if (arr[i] % j == 0) {
				cnt -= 1;
				break;
			}
		}
	}
	printf("%d \n", cnt);
	free(arr);
	return 0;
}