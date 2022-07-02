#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str[1000001];
	scanf("%[^\n]s", str);

	int count = 0;
	int len = strlen(str);

	for (int i = 0; i < len; i++){
		if (str[i] == ' '){
			if (i != 0 && i != len-1){
				count++;
			}
			if (len == 1){
				count = -1;
			}
		}
	}

	printf("%d\n", count + 1);
	exit(0);
}
