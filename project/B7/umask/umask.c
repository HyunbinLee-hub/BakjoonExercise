#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

// 파일 소유자, 그룹, 기타 사용자 모두 읽기, 쓰기 권한 보유
#define RW_MODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

// umask 설정 여부를 통해 생성 파일에 대한 사용자의 파일 접근 권한 제한
int main(void)
{
	char *fname1 = "ssu_file1";	// 생성 파일 1
	char *fname2 = "ssu_file2";	// 생성 파일 2

	umask(0);	// 접근권한 제한 없음

	// 모든 사용자에게 읽기, 쓰기 권한이 부여된 파일 생성
	if (creat(fname1, RW_MODE) < 0) {
		fprintf(stderr, "creat error for %s\n", fname1);
		exit(1);
	}

	// 그룹, 기타 사용자는 읽기, 쓰기 권한 제한
	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);

	// 파일 소유자만 읽기, 쓰기 가능한 파일 생성
	if (creat(fname2, RW_MODE) < 0) {
		fprintf(stderr, "creat error for %s\n", fname2);
		exit(1);
	}

	exit(0);
}
