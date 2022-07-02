#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int num[2] = {0,};
	char buffer[4] = { 0, };
	char temp;
	int res, i, max;
	
	res = 0;
	while (1) {
		if (res == 1) 
			break;
		scanf("%d", &num[0]);
		scanf("%d", &num[1]);
	
		if (num[0] < 100 || num[0] > 999)
			continue;
		if (num[1] < 100 || num[1] > 999)
			continue;
		if (num[0] == num[1])
			continue;
		res = 1;
	}

	for (i = 0; i < 2; i++) {
		sprintf(buffer, "%d", num[i]);
		temp = buffer[0];
		buffer[0] = buffer[2];
		buffer[2] = temp;
		num[i] = atoi(buffer);
		buffer[0] = 0;
	}
	
	max = (num[0] > num[1]) ? num[0] : num[1];
	printf("%d \n", max);
	return 0;
}