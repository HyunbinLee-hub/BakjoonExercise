#include <stdio.h>

int main(void)
{
	int num1, num2;

	while (1) {
		scanf("%d%d", &num1, &num2);
		if (num1 == 0 && num2 == 0)
			break;
		else if (num1 == 0 || num2 == 0)
			printf("neither\n");
		else {
			if (num1 % num2 == 0 || num2 % num1 == 0) {
				if (num1 > num2)
					printf("multiple\n");
				else
					printf("factor\n");
			}
			else {
				printf("neither\n");
			}
		}
	}
	return 0;
}