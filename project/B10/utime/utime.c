#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>

// 입력한 파일별 최종 접근 시간, 최종 수정 시간 갱신
int main(int argc, char *argv[])
{
	struct utimbuf time_buf;
	struct stat statbuf;
	int fd;
	int i;

	for (i = 1; i < argc; i++) {
		// 파일의 정보 불러오기
		if (stat(argv[i], &statbuf) < 0) {
			fprintf(stderr, "stat error for %s\n", argv[i]);
			continue;
		}
		
		// 파일 오픈 후 닫기: 최종 접근 및 수정 시간 변동 발생
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
			fprintf(stderr, "open error for %s\n", argv[i]);
			continue;
		}

		close(fd);

		// 최종 접근 시간, 최종 수정 시간 갱신
		time_buf.actime = statbuf.st_atime;
		time_buf.modtime = statbuf.st_mtime;

		if (utime(argv[i], &time_buf) < 0) {
			fprintf(stderr, "utime error for %s\n", argv[i]);
			continue;
		}
	}

	exit(0);
}
