#include <stdio.h>

int main(void)
{
	int initNum;
	int num, sum, res;
	int count = 1;

	while (1) {
		scanf("%d", &initNum);
		if (0 <= initNum && initNum <= 99)
			break;
		else printf("다시 입력하세요. \n");
	}

	num = initNum;
	while (1) {
		sum = (num / 10) + (num % 10);
		res = (num % 10) * 10 + (sum % 10);
		if (res == initNum)
			break;
		else {
			num = res;
			++count;
		}
	}

	printf("%d \n", count);
	return 0;
}