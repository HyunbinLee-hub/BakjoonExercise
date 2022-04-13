#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// 파일 림크 해제를 통한 파일 삭제
int main(void)
{
	char *fname = "ssu_dump.txt";

	// 읽기/쓰기 혼용으로 파일 오픈
	if (open(fname, O_RDWR) < 0) {
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	// 파일 링크 해제
	if (unlink(fname) < 0) {
		fprintf(stderr, "unlink error for %s\n", fname);
		exit(1);
	}

	printf("File unlinked\n");
	sleep(20);
	printf("Done\n");
	exit(0);
}
