#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculateScore(char * buffer)
{
	int sum = 0, stack;
	int i;

	for (i = 0; i < strlen(buffer); i++) {
		if (i == 0) {
			if (buffer[i] == 'O') stack = 1;
			else stack = 0;
		}
		else {
			if (buffer[i] == 'O' && buffer[i - 1] == 'O') {
				stack += 1;
			}
			else if (buffer[i] == 'O' && buffer[i - 1] == 'X') {
				stack = 1;
			}
			else if (buffer[i] == 'X' && buffer[i - 1] == 'O')
				stack = 0;
		}
		sum += stack;
	}
	return sum;
}
void showScore(int * score, const int trial)
{
	int i;
	for (i = 0; i < trial; i++)
		printf("%d \n", score[i]);
}

int main(void)
{
	int trial;
	char buffer[80];
	int * score;

	scanf("%d", &trial);
	score = (int *)calloc(trial, sizeof(int));

	for (int i = 0; i < trial; i++) {
		scanf("%s", buffer);
		score[i] = calculateScore(buffer);
		buffer[0] = 0;
	}

	showScore(score, trial);
	free(score);
	return 0;
}