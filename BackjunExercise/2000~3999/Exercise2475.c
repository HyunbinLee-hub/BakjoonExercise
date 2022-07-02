#include <stdio.h>

int main(void)
{
	int num[5] = { 0, };
	int sum = 0;
	for (int i = 0; i < sizeof(num) / sizeof(int); i++)
	{
		scanf("%d", &num[i]);
		sum += num[i] * num[i];
	}
	printf("%d\n", sum % 10);
	return 0;
}