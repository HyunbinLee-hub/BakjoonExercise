#include <stdio.h>	// fgets()가 정의된 헤더 파일
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024	// 입력에 사용할 버퍼 크기

int main(void)
{
	char buf[BUFFER_SIZE];

	// 줄 단위 문자 입력
	while (fgets(buf, BUFFER_SIZE, stdin) != NULL)
		// 출력할 문자열 없을 시 에러 처리
		if (fputs(buf, stdout) == EOF) {
			fprintf(stderr, "standard output error\n");
			exit(1);
		}
	// 문자열 입력 실패 시 에러 처리
	if (ferror(stdin)) {
		fprintf(stderr, "standard input error\n");
		exit(1);
	}

	exit(0);
}
