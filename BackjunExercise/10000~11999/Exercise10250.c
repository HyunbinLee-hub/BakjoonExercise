#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int cnt;
	int w, h, n;	// �� ���� �� ����, ȣ�� ��ü�� ����, n��° �մ�
	int i;
	int x = 0, y = 0;		// x�� �� �������� �� ��ȣ, y�� ����

	scanf("%d", &cnt);
	for (i = 0; i < cnt; i++) {
		/* w, h, n �Է�*/
		scanf("%d %d %d", &h, &w, &n);
		if (n % h == 0) {
			y = h;
			x = (n / h);
		}
		else {
			y = n % h;
			x = (n / h) + 1;
		}
		printf("%d%.2d\n", y, x);
	}

	return 0;
}