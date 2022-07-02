#include <stdio.h>

int Distance(int xpos1, int ypos1, int xpos2, int ypos2)
{
	int distance;
	distance = (xpos1 - xpos2)*(xpos1-xpos2) + (ypos1 - ypos2)*(ypos1-ypos2);
	return distance;
}

int main(void)
{
	int cnt;
	int xpos1, ypos1;
	int xpos2, ypos2;
	int r1, r2;
	int dis, res;

	scanf("%d", &cnt);
	for (int i = 0; i < cnt; i++) {
		scanf("%d%d%d%d%d%d", &xpos1, &ypos1, &r1, &xpos2, &ypos2, &r2);
		dis = Distance(xpos1, ypos1, xpos2, ypos2);
		if (xpos1 == xpos2 && ypos1 == ypos2) // 원의 중심이 같음
		{
			if (r1 == r2) res = -1;
			else res = 0;
		}
		else	// 원의 중심이 다름
		{
			if ((r1 + r2)*(r1 + r2) < dis) res = 0;
			else if ((r1+r2)*(r1+r2) == dis) res = 1;
			else if ((r1 + r2)*(r1 + r2) > dis && dis > (r1 - r2)*(r1 - r2)) res = 2;
			else if ((r1 - r2)*(r1 - r2) == dis) res = 1;
			else res = 0;
		}
		printf("%d\n", res);
	}
	return 0;
}