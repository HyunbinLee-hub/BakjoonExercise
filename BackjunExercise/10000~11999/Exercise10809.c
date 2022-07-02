#include <stdio.h>
#include <string.h>

int main(void)
{
	char word[100];
	int alphabet[26];
	int idx;

	scanf("%s", word);
	for (int i = 0; i < sizeof(alphabet) / sizeof(int); i++)
		alphabet[i] = -1;

	for (int i = 0; i < strlen(word); i++) {
		idx = word[i] - 'a';
		if (idx >= 0 && alphabet[idx] == -1)
			alphabet[idx] = i;
	}
	
	for (int i = 0; i < sizeof(alphabet) / sizeof(int); i++)
		printf("%d ", alphabet[i]);
	printf("\n");
	return 0;
}