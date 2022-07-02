#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int arrlen;
	int * arr;
	int i, max, min;

	/*배열 길이, 값 입력*/
	scanf("%d", &arrlen);
	arr = (int *)malloc(sizeof(int)*arrlen);
	for (i = 0; i < arrlen; i++)
		scanf("%d", &arr[i]);

	/* 최대 최소 비교 */
	max = arr[0];
	min = arr[0];
	for (i = 1; i < arrlen; i++) {
		max = (max >= arr[i]) ? max : arr[i];
		min = (min < arr[i]) ? min : arr[i];
	}

	printf("%d %d \n", min, max);

	free(arr);
	return 0;
}