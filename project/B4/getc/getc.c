#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int character;
	// 한 번에 한 글자씩 표준 입력에서 읽기 수행
	while ((character = getc(stdin)) != EOF) {
		// 한 번에 한 글자씩 표준 출력에 쓰기 수행
		if (putchar(character) == EOF) {
			fprintf(stderr, "standard output error\n");
			exit(1);
		}
	}
	// 데이터 입력 실패 시 에러 처리
	if (ferror(stdin)) {
		fprintf(stderr, "standard input error\n");
		exit(1);
	}

	exit(0);
}
