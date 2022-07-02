#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[101] = { 0, };
	int count;
	int len, i;

	scanf("%s", str);
	len = strlen(str);
	count = len;
	for (i = 1; i < len; i++) {
		if (str[i] == '-') {
			if (str[i - 1] == 'c' || str[i - 1] == 'd') --count;
		}
		else if (str[i] == 'j') {
			if (str[i - 1] == 'l' || str[i - 1] == 'n') --count;
		}
		else if (str[i] == '=') {
			if (str[i - 1] == 'c' || str[i - 1] == 's') --count;
			if (str[i - 1] == 'z') {
				--count;
				if (i >= 2 && str[i - 2] == 'd') --count;
			}
		}
	}

	printf("%d \n", count);
	return 0;
}