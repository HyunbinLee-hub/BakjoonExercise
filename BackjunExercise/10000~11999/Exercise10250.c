#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int cnt;
	int w, h, n;	// 각 층별 방 개수, 호텔 전체의 층수, n번째 손님
	int i;
	int x = 0, y = 0;		// x는 한 층에서의 방 번호, y는 층수

	scanf("%d", &cnt);
	for (i = 0; i < cnt; i++) {
		/* w, h, n 입력*/
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