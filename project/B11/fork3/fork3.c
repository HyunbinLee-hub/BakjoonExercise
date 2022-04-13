#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void ssu_charatatime(char *str);

// fork() 호출 시 부모 프로세스와는 별도로 자식 프로세스 생성
int main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0) {
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if (pid == 0)	// 자식 프로세스
		ssu_charatatime("output from child\n");	
	else			// 부모 프로세스 
		ssu_charatatime("output from parent\n");

	exit(0);
}

static void ssu_charatatime(char *str) 
{
	char *ptr;
	int print_char;

	// 버퍼링 없이 바로 출력
	setbuf(stdout, NULL);

	// 인자로 받은 문자열을 한 글자씩 출력
	// 부모 프로세스와 자식 프로세스는 별도로 동작
	for (ptr = str; (print_char = *ptr++) != 0; ) {
		putc(print_char, stdout);
		usleep(10);
	}
}