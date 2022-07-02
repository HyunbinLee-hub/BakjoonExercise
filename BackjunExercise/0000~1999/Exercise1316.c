#include <stdio.h>
#include <string.h>

int main(void)
{
	int cnt, grpCnt, len;
	char str[100] = {0,};
	int i, j;

	scanf("%d", &cnt);
	grpCnt = cnt;
	for (i = 0; i < cnt; i++) {
		int alphabet[26] = { 0, };
		char firstChar = '\0';

		scanf("%s", str);
		len = strlen(str);
		for (j = 0; j < len; j++) {
			if (firstChar != str[j]) {
				firstChar = str[j];
				alphabet[str[j] - 'a'] += 1;
			}
			if (alphabet[str[j] - 'a'] > 1) {
				grpCnt -= 1;
				break;
			}
		}
	}
	printf("%d \n", grpCnt);
	return 0;
}