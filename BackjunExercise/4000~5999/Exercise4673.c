#include <stdio.h>

void selfNumber(void)
{
	int constNum[10001] = {0,};
	int res;
	for (int i = 1; i < 10001; i++) {
		res = i + (i/1000) + (i%1000/100) + (i%100/10) + (i%10);
		if (res <= 10000)
			constNum[res]++;
		if (constNum[i] == 0)
			printf("%d \n", i);
	}
}
int main(void)
{
	selfNumber();
	return 0;
}