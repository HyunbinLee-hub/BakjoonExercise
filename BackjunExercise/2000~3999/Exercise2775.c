#include <stdio.h>

int main(void)
{
	int cnt, k, n;
	int i;

	scanf("%d", &cnt);
	for (i = 0; i < cnt; i++) {
		int arr[15][15] = { 0, };
		int j, m;

		scanf("%d", &k);
		scanf("%d", &n);

		for (j = 0; j <= k; j++) {	// 0������ ���
			int sum = 0;

			for (m = 1; m <= n; m++) {	// �� ���� 1ȣ���� nȣ������ ������ ����
				if (j == 0)
					arr[j][m] = m;
				else {
					sum += arr[j - 1][m];
					arr[j][m] += sum;
				}
			}
		}
		printf("%d \n", arr[k][n]);
	}
	return 0;
}