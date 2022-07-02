#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char num[7];
	int init, comp;
	int res = 0, ans = 0;
	int i, j;

	// 입력값
	scanf("%s", num);
	comp = atoi(num);
	num[0] = '\0';

	// 생성자 구하기
	for (i = 1; i <= comp; i++) {
		sprintf(num, "%d", i);
		res += i;
		
		for (j = 0; j < strlen(num); j++) {
			res += num[j] - '0';
		}

		if (res == comp) {
			ans = i;
			break;
		}
		res = 0;
	}

	printf("%d\n", ans);
	exit(0);
}
