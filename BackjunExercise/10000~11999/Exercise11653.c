#include <stdio.h>
#include <math.h>

int main(void)
{
	int num;
	int i;

	scanf("%d", &num);
	for (i = 2; i <= num; i++) {
		while (num % i == 0) {
			printf("%d \n", i);
			num /= i;
		}
	}
	return 0;
}