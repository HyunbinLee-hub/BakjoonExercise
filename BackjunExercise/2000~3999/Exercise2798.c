#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int num, m;
	int i, j, k;
	int capacity, count = 0;
	int val[100] = {0, };
	int arr[161700] = {0, };
	int min;

	/* 입력 */
	scanf("%d%d", &num, &m);
	capacity = num * (num-1) * (num-2) / 6;

	for (i = 0; i < num; i++)
	{
		scanf("%d", &val[i]);
	}

	/* 3장의 카드 선택 */
	for (i = 0; i < num-2; i++) 
	{
		for (j = i + 1; j < num-1; j++)
		{
			for (k = j + 1; k < num; k++)
			{
				arr[count] = val[i] + val[j] + val[k];
				count++;
			}
		}
	}

	/* 판정 */
	for (int i = 0; i < count; i++)
	{
		arr[i] = m - arr[i];

		if (arr[i] >= 0) {
			min = (min > arr[i]) ? arr[i] : min;
		}
	}
	
	printf("%d\n", m - min);
	exit(0);
}
