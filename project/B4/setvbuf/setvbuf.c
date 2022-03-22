#include <stdio.h>	//setvbuf()가 정의된 표준 입출력 헤더파일
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024	// 버퍼링용 버퍼 크기

void ssu_setbuf(FILE *fp, char *buf);

int main(void)
{
	char buf[BUFFER_SIZE];
	char *fname = "/dev/pts/0";	// 현재 터미널 장치 파일명
	FILE *fp;

	// 쓰기모드로 파일 오픈, 실패 시 에러 처리
	if ((fp = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	ssu_setbuf(fp, buf);	// 입출력 시 버퍼링 수행
	fprintf(fp, "Hello, "); sleep(1);
	fprintf(fp, "UNIX!!"); sleep(1);
	fprintf(fp, "\n"); sleep(1);	// 출력 버퍼를 거쳐 한번의 fprintf 호출로 출력
	ssu_setbuf(fp, NULL);		// 입출력 시 버퍼링 없음
	fprintf(fp, "HOW"); sleep(1);
	fprintf(fp, " ARE"); sleep(1);
	fprintf(fp, " YOU?"); sleep(1);
	fprintf(fp, "\n"); sleep(1);	// 각 fprintf 호출마다 출력
	exit(0);
}

void ssu_setbuf(FILE *fp, char *buf)
{
	size_t size;
	int fd;
	int mode;

	fd = fileno(fp);	// 오픈한 파일에 파일 디스크립터 번호 부여
	if (isatty(fd))		// 오픈한 파일이 터미널 장치 파일인 경우
		mode = _IOFBF;	// 버퍼 단위로 입출력
	else
		mode = _IOLBF;	// 줄 단위로 입출력
	if (buf == NULL) {
		mode = _IONBF;	// 출력 함수 호출마다 입출력(버퍼링 없음)
		size = 0;
	}
	else
		size = BUFFER_SIZE;	// 버퍼링 시 사용할 버퍼의 길이
	setvbuf(fp, buf, mode, size);	// 설정한 버퍼 크기, 버퍼링 방식대로 버퍼링
}
