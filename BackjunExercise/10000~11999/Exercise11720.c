#include <stdio.h>

int main(void)
{
	int cnt;
	char str[101];
	int i, sum = 0;

	scanf("%d", &cnt);
	getchar();
	for (i = 0; i < cnt; i++) {
		str[i] = getchar();
		sum += (str[i]-'0');
	}
	printf("%d \n", sum);
	return 0;
}