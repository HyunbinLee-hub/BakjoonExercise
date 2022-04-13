#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// 파일 링크 해제 시점 확인
int main(void)
{
	char buf[64];
	char *fname = "ssu_tempfile";
	int fd;
	int length;

	// 지정한 파일 생성 및 오픈
	if ((fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0600)) < 0) {
		fprintf(stderr, "first open error for %s\n", fname);
		exit(1);
	}

	// unlink 시스템 콜 호출 시작 시점
	if (unlink(fname) < 0) {
		fprintf(stderr, "unlink error for %s\n", fname);
		exit(1);
	}

	// 오픈한 파일에 문자열 입력 후 읽어서 출력: 정상 수행
	if (write(fd, "How are you?", 12) != 12) {
		fprintf(stderr, "write error\n");
		exit(1);
	}

	lseek(fd, 0, 0);

	if ((length = read(fd, buf, sizeof(buf))) < 0) {
		fprintf(stderr, "buf read error\n");
		exit(1);
	}
	else
		buf[length] = 0;

	printf("%s\n", buf);		// 읽어온 데이터 출력: 정상 수행
	close(fd);			// 파일 링크 해제 시점

	// 지정한 파일 오픈, 실패 시 에러 처리: 파일 삭제로 인해 에러 발생
	if ((fd = open(fname, O_RDWR)) < 0) {
		fprintf(stderr, "second open error for %s\n", fname);
		exit(1);
	}
	else
		close(fd);

	exit(0);
}
