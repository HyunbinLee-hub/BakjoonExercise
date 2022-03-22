#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
	char *fname = "ssu_test.txt";
	int fd;

	// ssu_test.txt 파일을 새로 생성, 실패 시 에러 처리
	if ((fd = creat(fname, 0666)) < 0) {
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1);
	}
	else {	// 파일 생성 성공 시 파일명, 파일디스크립터 번호 입력
		printf("Success!\nFilename: %s\nDescriptor: %d\n", fname, fd);
		close(fd);
	}

	exit(0);
}
