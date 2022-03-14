#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
	int count;
	int fd1, fd2;

	// 한 파일을 읽기 전용으로 여러 번 오픈
	fd1 = open(fname, O_RDONLY);
	fd2 = open(fname, O_RDONLY);

	// 한 번이라도 오픈 실패 시 에러 처리
	if (fd1 < 0 || fd2 < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	// 첫번째 오픈된 파일의 첫번째 줄을 문자열로 저장 후 출력
	count = read(fd1, buf, 25);
	buf[count] = 0;	
	printf("fd1's first printf :%s\n", buf);	
	lseek(fd1, 1, SEEK_CUR);			// 다음 줄로 이동
	// 파일의 두번째 줄을 문자열로 저장 후 출력
	count = read(fd1, buf, 24);
	buf[count] = 0;
	printf("fd1's second printf :%s\n", buf);	
	// 두번째 오픈된 파일의 첫번째 줄을 문자열로 저장 후 출력
	count = read(fd2, buf, 25);
	buf[count] = 0;
	printf("fd2's first printf :%s\n", buf);	
	lseek(fd2, 1, SEEK_CUR);			// 다음 줄로 이동
	// 파일의 두번째 줄을 문자열로 저장 후 출력
	count = read(fd2, buf, 24);
	buf[count] = 0;
	printf("fd2's second printf :%s\n", buf);

	exit(0);
}
