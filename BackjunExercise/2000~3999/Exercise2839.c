#include <stdio.h>

int main(void)
{
	int weight;
	int cnt = 0;
	int a, b;

	scanf("%d", &weight);
	if (weight >= 3 && weight <= 5000) {
		while (1) {
			if (weight % 5 == 0) {	// 5의 배수이면 몫만큼 횟수에 추가
				cnt += (weight / 5);
				break;
			}
			weight -= 3;	// 5의 배수가 아니면 무게에서 3을 뺀 횟수만큼 전체 횟수에 추가
			cnt++;
			if (weight <= 0) {
				if (weight < 0)
					cnt = -1;
				break;
			}
		}
		printf("%d \n", cnt);
	}

	return 0;
}