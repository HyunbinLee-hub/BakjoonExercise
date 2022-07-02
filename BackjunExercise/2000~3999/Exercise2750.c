#include <stdio.h>

void BubbleSort(int arr[], int len)
{
	for (int i = 0; i < len-1; i++) {
		for (int j = 0; j < (len-i)-1; j++) 
		{
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main(void)
{
	int arr[1001] = { 0, };
	int len;

	scanf("%d", &len);
	for (int i = 0; i < len; i++)
		scanf("%d", &arr[i]);
	BubbleSort(arr, len);

	for (int i = 0; i < len; i++)
		printf("%d\n", arr[i]);
	return 0;
}