#include <stdio.h>
#include <string.h>

int main(void)
{
	int alphabet[26] = { 0, };	// 알파벳별 사용 개수
	char str[1000000] = { 0, };			// 문자열의 최대 길이
	int len, i, max;
	int idx;

	scanf("%s", str);
	len = strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] >= 'a' && str[i] <= 'z')
			++alphabet[str[i] - 'a'];
		else if (str[i] >= 'A' && str[i] <= 'Z')
			++alphabet[str[i] - 'A'];
	}

	max = alphabet[0];
	idx = 0;
	len = sizeof(alphabet) / sizeof(int);
	for (i = 1; i < len; i++) {
		if (max < alphabet[i]) {
			max = alphabet[i];
			idx = i;
		}
		else if (max == alphabet[i])
			idx = -1;
	}
	
	if (idx == -1)
		printf("? \n");
	else
		printf("%c \n", 'A' + idx);

	return 0;
}