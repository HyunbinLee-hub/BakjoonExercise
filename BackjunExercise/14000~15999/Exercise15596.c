#include <stdio.h>
#include <stdlib.h>

long long sum(int *a, int n)
{
	long long res = 0;
	for (int i = 0; i < n; i++)
		res += a[i];
	return res;
}

int main(void)
{
	int count;
	int * num;
	long long res;
	int i;

	scanf("%d", &count);
	num = (int *)calloc(count, sizeof(int));
	for (i = 0; i < count; i++)
		scanf("%d", &num[i]);
	res = sum(num, count);
	printf("%lld \n", res);

	free(num);
	return 0;
}