#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int caseCnt, student;
	int score[1000] = {0,};
	double avg = 0.0; 
	double percent = 0.0;
	int sum = 0, cnt = 0;

	scanf("%d", &caseCnt);

	for (int i = 0; i < caseCnt; i++) {
		/* 한 케이스에서의 학생 수 입력*/
		scanf("%d", &student);

		/* 한 케이스 내 모든 학생들의 점수 입력 및 평균 계산*/
		sum = 0;
		for (int i = 0; i < student; i++) {
			scanf("%d", &score[i]);
			sum += score[i];
		}
		avg = (double)sum / student;

		/* 평균을 넘는 학생들의 비율 계산*/
		cnt = 0;
		for (int i = 0; i < student; i++) {
			if ((double)score[i] > avg)
				cnt++;
		}
		percent = (double)cnt*100 / student;
		printf("%.3lf%% \n", percent);
	}

	return 0;
}