#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// 파일 이름 변경
int main(int argc, char *argv[])
{
	int fd;

	// 인자의 개수 확인
	if (argc != 3) {
		fprintf(stderr, "usage: %s <oldname> <newname>\n", argv[0]);
		exit(1);
	}

	// 기존 파일 첫번째 오픈, 실패 시 에러 처리
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "first open error for %s\n", argv[1]);
		exit(1);
	}
	else
		close(fd);

	// 기존 파일의 이름을 새로운 이름으로 변경
	if (rename(argv[1], argv[2]) < 0) {
		fprintf(stderr, "rename error\n");
		exit(1);
	}

	// 기존 파일명으로 두번째 오픈, 성공 시 에러 처리
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		printf("second open error for %s\n", argv[1]);
	}
	else {
		fprintf(stderr, "it's very strange!\n");
		exit(1);
	}

	// 새로운 파일명으로 파일 오픈, 실패 시 에러 처리
	if ((fd = open(argv[2], O_RDONLY)) < 0) {
		fprintf(stderr, "third open error for %s\n", argv[2]);
		exit(1);
	}

	printf("Everything is good!\n");
	exit(0);
}
