#include <stdio.h>
#include <stdlib.h>

// 라이브러리 함수를 이용한 파일 크기 출력
int main(void)
{
	char *fname = "ssu_test.txt";
	FILE *fp;
	long fsize;	// 파일의 크기

	// 읽기전용으로 파일 오픈
	if ((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	fseek(fp, 0L, SEEK_END);	// 파일 오프셋을 맨 끝으로 이동
	fsize = ftell(fp);		// 현재 오프셋 값 = 파일 크기
	printf("The size of <%s> is %ld bytes\n", fname, fsize);
	exit(0);
}
