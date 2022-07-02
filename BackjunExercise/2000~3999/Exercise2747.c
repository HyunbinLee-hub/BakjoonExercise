#include <stdio.h>

int main(void)
{
	int num;

	scanf("%d", &num);
	int a = 0;
	int b = 1;
	int c = 1;

	for (int i = 1; i < num; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	printf("%d\n", c);
	return 0;
}