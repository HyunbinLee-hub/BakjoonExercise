#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char character;		// 읽어온 문자 저장
	int fd;
	int line_count = 0;	// 파일의 줄 개수

	// 파일 오픈, 실패 시 에러 처리
	if ((fd = open("ssu_test.txt", O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", "ssu_test.txt");
		exit(1);
	}

	while (1) {
		// 한 글자씩 읽기 수행하며 파일의 줄 개수 카운트
		if (read(fd, &character, 1) > 0) {
			if (character == '\n')
				line_count++;
		}
		else	// 더 이상 읽어올 수 없으면 종료
			break;
	}

	// 파일의 줄 개수 출력
	printf("Total line : %d\n", line_count);
	exit(0);
}
