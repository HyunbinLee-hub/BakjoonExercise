#include <stdio.h>

int main(void)
{
	int weight;
	int cnt = 0;
	int a, b;

	scanf("%d", &weight);
	if (weight >= 3 && weight <= 5000) {
		while (1) {
			if (weight % 5 == 0) {	// 5�� ����̸� ��ŭ Ƚ���� �߰�
				cnt += (weight / 5);
				break;
			}
			weight -= 3;	// 5�� ����� �ƴϸ� ���Կ��� 3�� �� Ƚ����ŭ ��ü Ƚ���� �߰�
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