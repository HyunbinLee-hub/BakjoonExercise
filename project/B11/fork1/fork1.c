#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 전역 범위
char glob_str[] = "write to standard output\n";
int glob_val = 10;

int main(void)
{
	pid_t pid;
	int loc_val;	// 지역변수

	loc_val = 100;
	// fork() 호출 이전 문자열은 바로 출력
	if (write(STDOUT_FILENO, glob_str, sizeof(glob_str)-1) != sizeof(glob_str)-1) {
		fprintf(stderr, "write error\n");
		exit(1);
	}
	// 출력 시 버퍼링 실시, 부모 프로세스 재개 시 버퍼 내 문자열 출력
	printf("before fork\n");
	
	// 프로세스 생성 실패
	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if (pid == 0) {	// 자식 프로세스
		glob_val++;
		loc_val++;
	}
	else			// 부모 프로세스
		sleep(3);

	// 자식 프로세스와 부모 프로세스에서 각각 출력
	// 부모 프로세스 재개 시 버퍼에 남은 모든 문자열 출력
	printf("pid = %d, glob_val = %d, loc_val = %d\n", getpid(), glob_val, loc_val);
	exit(0);	// 자식, 부모 프로세스 종료 시점
}