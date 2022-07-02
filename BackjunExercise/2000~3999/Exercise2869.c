#include <stdio.h>

int main(void)
{
	long a, b, v;
	long days;

	scanf("%d %d %d", &a, &b, &v);
	days = (v - b - 1) / (a - b) +1;
	printf("%d \n", days);
	return 0;
}