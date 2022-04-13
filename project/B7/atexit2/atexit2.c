#include <stdio.h>
#include <stdlib.h>

static void ssu_exit1(void);	// 종료 메시지 출력1
static void ssu_exit2(void);	// 종료 메시지 출력2

// 프로그램 종료 시 여러 개의 함수를 출력할 경우, 호출 순서의 역순으로 출력
int main(void)
{
	// 프로그램 종료 시 메시지 출력1: 마지막으로 출력
	if (atexit(ssu_exit2) != 0) {
		fprintf(stderr, "atexit error for ssu_exit2\n");
		exit(1);
	}

	// 프로그램 종료 시 메시지 출력2: 두번째로 출력
	if (atexit(ssu_exit1) != 0) {
		fprintf(stderr, "atexit error for ssu_exit1\n");
		exit(1);
	}

	// 프로그램 종료 시 메시지 출력: 첫번째로 출력
	if (atexit(ssu_exit1) != 0) {
		fprintf(stderr, "atexit error for ssu_exit1\n");
		exit(1);
	}

	printf("done\n");
	exit(0);
}

static void ssu_exit1(void)
{
	printf("ssu_exit1 handler\n");
}

static void ssu_exit2(void)
{
	printf("ssu_exit2 handler\n");
}
