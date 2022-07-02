#include <stdio.h>
#define PI 3.141592653589793

int main(void)
{
	int rad;
	double result1, result2;

	scanf("%d", &rad);
	result1 = (double)rad*rad*PI;
	result2 = (double)rad*rad * 2;
	printf("%.6lf\n%.6lf", result1, result2);
	return 0;
}