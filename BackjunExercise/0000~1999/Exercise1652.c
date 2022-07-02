#include <stdio.h>
#include <stdlib.h>

// 배열 초기화 함수
void initArray(int (*arr)[100], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			arr[i][j] = 1;
		}
	}
}
// 배열 출력 함수(디버깅용)
void printArray(int (*arr)[100], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d ", arr[i][j]); 
		}
		printf("\n");
	}
}

// 가로로 누울 수 있는 자리 개수
// 현재 칸이 짐 = 연속 종료, 누울 자리인지 판정
// 현재 칸이 빈 칸 = 빈 공간 길이 카운트 시작
int countHorLine(int (*arr)[100], int size)
{
	int i;
	int count = 0;

	for (i = 0; i < size; i++)
	{
		int len = 0;
		int j = 0;
		
		// 첫번째 칸
		if (j == 0) 
		{
			if (arr[i][j] == 0) len++;
			else len = 0;
		}

		// 중간 칸
		for (j = 1; j < size-1; j++)
		{
			// 앞뒤로 모두 같은 값
			if (arr[i][j-1] == arr[i][j] && arr[i][j] == arr[i][j+1])
			{
				if (arr[i][j] == 0)	// 빈 공간이 연속 
					len++;
				else 			// 짐이 연속
					len = 0;
			}
			// 새로운 연속 시작
			else if (arr[i][j-1] != arr[i][j] && arr[i][j] == arr[i][j+1])
			{
				if (arr[i][j] == 0)	// 현재 칸이 빈 공간
					len++;
				else {			// 현재 칸이 짐
					if (len >= 2) count++;
					len = 0;
				}
			}
			// 기존 연속 종료
			else if (arr[i][j-1] == arr[i][j] && arr[i][j] != arr[i][j+1])
			{
				if (arr[i][j] == 0)
				{
					len++;
				}
				else {
					if (len >= 2) count++;
					len = 0;
				}
			}
			// 기존 연속 종료 직후 새로운 연속 시작
			else // arr[i][j-1] != arr[i][j] && arr[i][j] != arr[i][j+1]
			{
				if (arr[i][j] == 0) len++;
				else {
					if (len >= 2) count++;
				}
				len = 0;
			}
		}

		// 마지막 칸
		if (j == size-1)
		{
			if (arr[i][j-1] == arr[i][j])
			{
				if (arr[i][j] == 0) {
					len++;
					if (len >= 2) count++;
				}
				else len = 0;
			}
			else	// arr[i][j-1] != arr[i][j]
			{
				if (arr[i][j] == 0) len++;
				else {
					if (len >= 2) count++;
				}
			}
		}
	}

	return count;
}
// 세로로 누울 수 있는 자리 개수
int countVerLine(int (*arr)[100], int size)
{
	int i;
	int count = 0;

	for (i = 0; i < size; i++)
	{
		int len = 0;
		int j = 0;

		if (j == 0) 
		{
			if (arr[j][i] == 0) len++;
			else len = 0;
		}

		for (j = 1; j < size-1; j++)
		{
			if (arr[j-1][i] == arr[j][i] && arr[j][i] == arr[j+1][i])
			{
				if (arr[j][i] == 0) 
					len++;
				else 
					len = 0;
			}
			else if (arr[j-1][i] != arr[j][i] && arr[j][i] == arr[j+1][i])
			{
				if (arr[j][i] == 0)
					len++;
				else {
					if (len >= 2) count++;
					len = 0;
				}
			}
			else if (arr[j-1][i] == arr[j][i] && arr[j][i] != arr[j+1][i])
			{
				if (arr[j][i] == 0)
				{
					len++;
				}
				else {
					if (len >= 2) count++;
					len = 0;
				}
			}
			else // arr[j-1][i] != arr[j][i] && arr[j][i] != arr[j+1][i]
			{
				if (arr[j][i] == 0) len++;
				else {
					if (len >= 2) count++;
				}
				len = 0;
			}
		}

		if (j == size-1)
		{
			if (arr[j-1][i] == arr[j][i])
			{
				if (arr[j][i] == 0) {
					len++;
					if (len >= 2) count++;
				}
				else len = 0;
			}
			else	// arr[i][j-1] != arr[i][j]
			{
				if (arr[j][i] == 0) len++;
				else {
					if (len >= 2) count++;
				}
			}
		}
	}

	return count;

}

int main(void)
{
	int size;
	int room[100][100];
	int i, j;

	initArray(room, 100);

	scanf("%d", &size);
	getchar();

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (getchar() == '.')
				room[i][j] = 0;
			else
				room[i][j] = 1;
		}
		getchar();
	}

	printf("%d ", countHorLine(room, size));
	printf("%d\n", countVerLine(room, size));

	exit(0);
}