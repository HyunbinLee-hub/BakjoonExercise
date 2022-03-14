#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// lseek() 시스템 콜 정의
#include <fcntl.h>
#include <sys/types.h>	// lseek()의 두번째 인자 offset의 자료형 정의

int main(void)
{
	char *fname = "ssu_test.txt";	// 사용할 파일
	off_t fsize;			// lseek()으로 구한 파일 크기 저장
	int fd;				// 파일 디스크립터: lseek() 첫 번째 인자

	// 읽기 전용으로 파일 오픈, 실패 시 에러 처리
	if ((fd = open(fname, O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	// 파일 크기 계산 : 파일의 시작부터 끝까지의 바이트 수
	if ((fsize = lseek(fd, 0, SEEK_END)) < 0) {
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	printf("The size of <%s> is %ld bytes\n", fname, fsize);

	exit(0);
}
