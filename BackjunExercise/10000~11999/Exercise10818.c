#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int arrlen;
	int * arr;
	int i, max, min;

	/*�迭 ����, �� �Է�*/
	scanf("%d", &arrlen);
	arr = (int *)malloc(sizeof(int)*arrlen);
	for (i = 0; i < arrlen; i++)
		scanf("%d", &arr[i]);

	/* �ִ� �ּ� �� */
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