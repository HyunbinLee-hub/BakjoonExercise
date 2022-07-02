#include <stdio.h>
#include <stdlib.h>

double findMax(double * arr, const int arrlen)
{
	double max;
	int i;

	max = arr[0];
	for (i = 0; i < arrlen; i++)
		max = (max >= arr[i]) ? max : arr[i];
	return max;
}

int main(void)
{
	int arrlen;
	double * score, max = 0, sum = 0;
	int i;

	scanf("%d", &arrlen);
	score = (double *)malloc(sizeof(double)*arrlen);
	for (i = 0; i < arrlen; i++)
		scanf("%lf", &score[i]);

	max = findMax(score, arrlen);
	for (i = 0; i < arrlen; i++) {
		score[i] = (score[i] / max) * 100;
		sum += score[i];
	}
	printf("%lf \n", sum / arrlen);
	free(score);
	return 0;
}