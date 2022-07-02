#include <stdio.h>

void TurningCount(int num1, int num2)
{
	int val;
	
	if (num1 < num2)
		val = num1;
	else
		val = num2;

	for (int i = 2; i <= val; i++) {
		while (num1 % i == 0 && num2 % i == 0)
		{
			num1 /= i;
			num2 /= i;
		}
	}
	printf("%d/%d\n", num1, num2);
}

int main(void)
{
	int cnt;
	int ring[1001] = { 0, };

	scanf("%d", &cnt);
	if (cnt > 2 && cnt < 101) {
		for (int i = 0; i < cnt; i++) {
			scanf("%d", &ring[i]);
		}

		for (int i = 1; i < cnt; i++) {
			TurningCount(ring[0], ring[i]);
		}
	}
	return 0;
}