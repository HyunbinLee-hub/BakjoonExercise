#include <stdio.h>

int fibonacci(int num) 
{
	if (num == 0)
		return 0;
	else if (num == 1)
		return 1;
	else
		return fibonacci(num - 2) + fibonacci(num - 1);
}

int main(void)
{
	int cnt;
	int res;
	scanf("%d", &cnt);
	if (cnt == 0 || (cnt > 0 && cnt < 21)) {
		res = fibonacci(cnt);
		printf("%d \n", res);
	}
	return 0;
}