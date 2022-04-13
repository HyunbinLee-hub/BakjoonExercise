#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// 출력할 내용이 표준 출력 대신 생성한 파일에 출력되도록 리다이렉트
int main(void)
{
	char *fname = "ssu_test.txt";	// 파일명
	int fd;

	// 파일 생성 및 오픈, 실패 시 에러 처리
	if ((fd = creat(fname, 0666)) < 0) {
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1);
	}

	// 표준 출력에 출력
	printf("First printf is on the screen.\n");
	// 파일 디스크립터를 1번 파일 디스크립터(표준 출력)로 복사
	// 리다이렉트 작업
	dup2(fd, 1);
	printf("Second printf is in this file.\n");
	exit(0);
}
