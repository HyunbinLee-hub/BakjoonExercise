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
		/* �� ���̽������� �л� �� �Է�*/
		scanf("%d", &student);

		/* �� ���̽� �� ��� �л����� ���� �Է� �� ��� ���*/
		sum = 0;
		for (int i = 0; i < student; i++) {
			scanf("%d", &score[i]);
			sum += score[i];
		}
		avg = (double)sum / student;

		/* ����� �Ѵ� �л����� ���� ���*/
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