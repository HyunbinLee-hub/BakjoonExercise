#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int hour;
	int min;
	int time;

	while (1) {
		scanf("%d%d", &hour, &min);
		if (hour < 0 || hour > 23)
			continue;
		else if (min < 0 || min > 59)
			continue;
		else
			break;
	}

	scanf("%d", &time);

	min += (time % 60);
	if (min > 59) {
		hour += 1;
		min -= 60;
		if (hour > 23) hour -= 24;
	}

	hour += (time / 60);
	if (hour > 23) hour -= 24;

	printf("%d %d\n", hour, min);
	exit(0);
}
