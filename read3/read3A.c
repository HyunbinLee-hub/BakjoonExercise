#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char c;
	int fd;

	// 파일 오픈, 실패 시 에러 처리
	if ((fd = open("ssu_test.txt", O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", "ssu_test.txt");
		exit(1);
	}

	while (1) {
		// 더 이상 읽을 수 없을 때까지 한 글자씩 읽고 출력
		if (read(fd, &c, 1) > 0)
			putchar(c);
		else
			break;
	}

	exit(0);
}
