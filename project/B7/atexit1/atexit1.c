#include <stdio.h>
#include <stdlib.h>

void ssu_out(void);	// 종료 메시지 출력 함수

// 프로그램 실행 종료 시점에서 함수 호출로 메시지 출력
int main(void)
{
	// 실행 종료 시 종료 메시지 출력
	if (atexit(ssu_out)) {
		fprintf(stderr, "atexit error\n");
		exit(1);
	}

	exit(0);
}

void ssu_out(void) {
	printf("atexit succeeded!\n");
}
