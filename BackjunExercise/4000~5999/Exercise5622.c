#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[16];
	int res, len;
	int sec;
	int i;
	
	res = 0;
	while (res != 1) {
		scanf("%s", str);
		len = strlen(str);
		if (len < 2 || len > 15) continue;
		res = 1;
	}

	sec = 0;
	for (i = 0; i < len; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 32;
		if (str[i] >= 'A' && str[i] <= 'Z') {
			if (str[i] >= 'A' && str[i] <= 'C') sec += 3;
			else if (str[i] <= 'F') sec += 4;
			else if (str[i] <= 'I') sec += 5;
			else if (str[i] <= 'L') sec += 6;
			else if (str[i] <= 'O') sec += 7;
			else if (str[i] <= 'S') sec += 8;
			else if (str[i] <= 'V') sec += 9;
			else sec += 10;
		}
	}

	printf("%d \n", sec);
	return 0;
}