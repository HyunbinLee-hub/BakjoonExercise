#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

struct stat statbuf;

void ssu_checkfile(char *fname, time_t *time);

// 파일 수정 때마다 수정 시간 갱신 및 알림 메시지 출력
int main(int argc, char *argv[])
{
	time_t intertime;	// 수정 시간 갱신용

	// 인자의 개수 확인
	if (argc != 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(1);
	}

	// 파일의 정보 가져오기
	if (stat(argv[1], &statbuf) < 0) {
		fprintf(stderr, "stat error for %s\n", argv[1]);
		exit(1);
	}

	// 수정 전 시간 = 현재 파일의 최종 수정 시간
	intertime = statbuf.st_mtime;
	while(1) {
		ssu_checkfile(argv[1], &intertime);
		sleep(10);
	}
}

void ssu_checkfile(char *fname, time_t *time)
{
	// 정보를 저장할 파일이 존재하지 않을 시 에러 처리
	if (stat(fname, &statbuf) < 0) {
		fprintf(stderr, "Warning : ssu_checkfile() error!\n");
		exit(1);
	}
	else	// 파일 정보 불러오기에 성공
		// 최종 수정시간이 다를 시 최근 시간으로 갱신
		if (statbuf.st_mtime != *time) {
			printf("Warning : %s was modified!.\n", fname);
			*time = statbuf.st_mtime;
		}
}
