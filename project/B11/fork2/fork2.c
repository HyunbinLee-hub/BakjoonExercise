#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid;			// 프로세스 id
	char character, first, last;
	long i;

	if ((pid = fork()) > 0) {	// 프로세스 생성 에러
		first = 'A';
		last = 'Z';
	}
	else if (pid == 0) {		// 자식 프로세스
		first = 'a';
		last = 'z';
	}
	else {				// 부모 프로세스
		fprintf(stderr, "%s\n", argv[0]);
		exit(1);
	}

	// fork() 호출 시점부터 자식 프로세스 생성 및 동작
	// 부모 프로세스와 자식 프로세스의 작업은 별개로 수행
	for (character = first; character <= last; character++) {
		for (i = 0; i <= 100000; i++)
			;

		write(1, &character, 1);
	}

	printf("\n");
	exit(0);
}