#include <stdio.h>

void countHan(int maxNum)
{
	int count = 0;
	int digit[3] = {0, 0, 0};
	
	for (int i = 1; i <= maxNum; i++) {
		if (maxNum < 100) ++count;
		else if (maxNum <= 1000){
			if (i < 100) ++count;
			else if (i < 1000) {
				digit[0] = i % 10;
				digit[1] = i % 100 / 10;
				digit[2] = i / 100;
				if (digit[1] - digit[0] == digit[2] - digit[1])
					++count;
			}
		}
	}
	
	printf("%d \n", count);
}

int main(void)
{
	int maxNum;
	int result;
	scanf("%d", &maxNum);
	countHan(maxNum);
	return 0;
}