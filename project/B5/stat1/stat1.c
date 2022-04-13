#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

// stat 구조체로 지정된 파일의 크기를 구한 후 출력
int main(int argc, char *argv[])
{
	struct stat statbuf;

	// 인자의 개수 확인
	if (argc != 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(1);
	}

	// 지정된 파일의 정보 읽어오기
	if (stat(argv[1], &statbuf) < 0) {
		fprintf(stderr, "stat error\n");
		exit(1);
	}

	// 파일의 크기 출력
	printf("%s is %ld bytes\n", argv[1], statbuf.st_size);
	exit(0);
}
