#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>	// creat() 세번째 인자인 mode 플래그 정의
#include <sys/types.h>	// mode의 자료형 정의
#include <fcntl.h>

int main(void)
{
	char *fname = "ssu_test.txt";	// 셍성/오픈할 파일 이름
	int fd;

	// 파일 새로 생성 후 오픈, 실패 시 에러 처리
	if ((fd = creat(fname, 0666)) < 0) {
		fprintf(stderr, "creat error for %s\n", fname);
		exit(1);
	}
	else {	// 파일을 닫은 후 권한을 읽기/쓰기 혼용으로 변경하여 오픈
		close(fd);
		fd = open(fname, O_RDWR);
		printf("Succeeded!\n<%s> is new readable and writable\n", fname);
	}

	exit(0);
}
