#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int cnt1, cnt2;
	char str[20] = {0,};
	int i, j, k;

	scanf("%d", &cnt1);
	for (i = 0; i < cnt1; i++) {
		scanf("%d", &cnt2);
		scanf("%s", str);
		for (j = 0; j < strlen(str); j++) {
			for (k = 0; k < cnt2; k++)
				putchar(str[j]);
		}
		str[0] = '\0';
		printf("\n");
	}
	
	return 0;
}