#include <stdio.h>

int main(void)
{
	int hour;
	int minute;

	while (1) {
		scanf("%d", &hour);
		scanf("%d", &minute);
		if ((0 <= hour && hour <= 23) && (0 <= minute && minute <= 59))
			break;
		else
			printf("�ٽ� �Է��ϼ���.\n");
	}

	if (minute < 45) {
		if (hour == 0)
			hour += 23;
		else --hour;
		minute += 15;
	}
	else
		minute -= 45;

	printf("%d %d \n", hour, minute);
	return 0;
}