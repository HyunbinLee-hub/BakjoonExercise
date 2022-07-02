#include <stdio.h>

int main(void)
{
	int arr[9];
	int i, max;
	int idx;

	for (i = 0; i < sizeof(arr) / sizeof(int); i++)
		scanf("%d", &arr[i]);

	max = arr[0];
	idx = 0;
	for (i = 1; i < sizeof(arr) / sizeof(int); i++) {
		if (max < arr[i]) {
			max = arr[i];
			idx = i;
		}
	}

	printf("%d \n", max);
	printf("%d \n", idx+1);
	return 0;
}