#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// 사용자는 읽기, 쓰기 모두 가능, 나머지는 읽기만 가능
#define CREAT_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// 생성할 파일에 추가할 버퍼
char buf1[] = "1234567890";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
	char *fname = "ssu_hole.txt";	// 사용할 파일
	int fd;

	// ssu_hole.txt 파일 생성, 실패 시 에러 처리
	if ((fd = creat(fname, CREAT_MODE)) < 0) {
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1);
	}

	// 생성한 파일에 buf1의 데이터 쓰기
	if (write(fd, buf1, 12) != 12) {
		fprintf(stderr, "buf1 write error\n");
		exit(1);
	}

	// buf1과 buf2의 문자열 사이에 15000bytes의 공백 발생
	if (lseek(fd, 15000, SEEK_SET) < 0) {
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	// 현재 오프셋에서 buf2의 데이터 쓰기
	if (write(fd, buf2, 12) != 12) {
		fprintf(stderr, "buf2 write error\n");
		exit(1);
	}

	exit(0);
}
