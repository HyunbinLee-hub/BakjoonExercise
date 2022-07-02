#include <stdio.h>

void countNum(char *arr) {
	int num[10];
	int i;

	for (i = 0; i < 10; i++) num[i] = 0;
	for (i = 0; i < 9; i++) {
		switch (arr[i] - '0') 
		{
		case 0:
			num[0]++;
			break;
		case 1:
			num[1]++;
			break;
		case 2:
			num[2]++;
			break;
		case 3:
			num[3]++;
			break;
		case 4:
			num[4]++;
			break;
		case 5:
			num[5]++;
			break;
		case 6:
			num[6]++;
			break;
		case 7:
			num[7]++;
			break;
		case 8:
			num[8]++;
			break;
		case 9:
			num[9]++;
			break;
		}
	}
	for (i = 0; i < 10; i++)
		printf("%d \n", num[i]);
}

int main(void)
{
	int num[3];
	int i;
	int res;
	char str[10];

	for (i = 0; i < 3; i++) {
		scanf("%d", &num[i]);
		if (num[i] < 100 || num[i] >= 1000) {
			printf("다시 입력하세요.\n");
			getchar();
			i--;
		}
	}

	res = num[0] * num[1] * num[2];
	sprintf(str, "%d", res);
	countNum(str);
	return 0;
}