#include <stdio.h>
#include <stdlib.h>

// 파일의 n번째 문자 출력
int main(void)
{
	char *fname = "ssu_test.txt";
	FILE *fp;
	long position;
	int character;

	// 읽기 전용으로 파일 오픈
	if ((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	// 입력한 오프셋값에 해당하는 위치의 문자 출력
	printf("Input number >>");
	scanf("%ld", &position);
	fseek(fp, position-1, SEEK_SET); // 파일의 시작점으로 오프셋 위치 초기화
	character = getc(fp);
	printf("%ldth character => %c\n", position, character);
	exit(0);
}
