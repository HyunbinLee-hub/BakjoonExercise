#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

// 다른 파일 디스크립터가 표준 출력의 출력작업 수행
int main(void)
{
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
	int fd;
	int length;

	// 읽기 전용 파일 오픈, 실패 시 에러 처리
	if ((fd = open(fname, O_RDONLY, 0644)) < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	// 4번 디스크립터가 표준 출력 수행하도록 파일 디스크립터 복사
	if (dup2(1, 4) != 4) {
		fprintf(stderr, "dup2 call failed\n");
		exit(1);
	}

	// 파일에 저장된 데이터의 크기만큼 읽어서 출력
	while (1)
	{
		length = read(fd, buf, BUFFER_SIZE);

		if (length <= 0)	// 파일 끝 도달 시 반복 종료
			break;

		write(4, buf, length);
	}

	exit(0);
}
