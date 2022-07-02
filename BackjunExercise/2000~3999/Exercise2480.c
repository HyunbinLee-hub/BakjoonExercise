#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int val[3] = {0, };
	int res = 0;
	int max = 0;

	while (1) 
	{
		scanf("%d%d%d", &val[0], &val[1], &val[2]);

		if (val[0] < 1 || val[0] > 6)
			continue;
		else if (val[1] < 1 || val[1] > 6)
			continue;
		else if (val[2] < 1 || val[2] > 6)
			continue;
		else
			break;
	}

	if (val[0] == val[1] && val[1] == val[2])
	{
		res = 10000 + val[0] * 1000;
	}
	else if (val[0] != val[1] && val[1] != val[2] && val[0] != val[2])
	{
		max = val[0];

		for (int i = 1; i < 3; i++) {
		       max = (max < val[i]) ? val[i] : max;
		}

		res = max * 100;
	}
	else 
	{
		res += 1000;

		if (val[0] == val[1])
			res += val[0] * 100;
		else if (val[2] == val[0])
			res += val[2] * 100;
		else
			res += val[1] * 100;
	}

	printf("%d\n", res);
}
