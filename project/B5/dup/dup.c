#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

// 서로 다른 파일 디스크립터에서 동일한 파일 내용 출력
int main(void)
{
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
	int fd1, fd2;
	int count;

	// 읽기 전용으로 파일 오픈
	// 사용자만 쓰기 가능
	if ((fd1 = open(fname, O_RDONLY, 0644)) < 0)
	{
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	fd2 = dup(fd1);	// 오픈한 파일의 파일 디스크립터 번호 복사
	// 원본 파일에서 12바이트 읽고 문자열 출력
	count = read(fd1, buf, 12);
	buf[count] = 0;
	printf("fd1's printf : %s\n", buf);
	// fd1과 fd2는 오프셋을 공유, 다음 글자부터 12바이트 읽고 문자열 출력
	lseek(fd1, 1, SEEK_CUR);
	count = read(fd2, buf, 12);
	buf[count] = 0;
	printf("fd2's printf : %s\n", buf);

	exit(0);
}
