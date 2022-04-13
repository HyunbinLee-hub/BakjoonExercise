#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

// 명령행 인자로 지정된 파일의 종류 출력
int main(int argc, char *argv[])
{
	struct stat file_info;	// 파일 정보 저장
	char *str;		// 파일 유형
	int i;

	// 명령행 인자별 파일 유형 출력
	for (i = 1; i < argc; i++) {
		// 파일 정보 불러오기
		if (lstat(argv[i], &file_info) < 0) {
			fprintf(stderr, "lstat error\n");
			continue;
		}

		if (S_ISREG(file_info.st_mode))		// 정규 파일
			str = "regular";
		else if (S_ISDIR(file_info.st_mode))	// 디렉토리 파일
			str = "directory";
		else if (S_ISCHR(file_info.st_mode))	// 문자 특수 파일
			str = "chracter special";
		else if (S_ISBLK(file_info.st_mode))	// 블록 특수 파일
			str = "block special";
		else if (S_ISFIFO(file_info.st_mode))	// FIFO 파일
			str = "FIFO";
		else if (S_ISLNK(file_info.st_mode))	// 심볼릭 링크
			str = "symbolic link";
		else if (S_ISSOCK(file_info.st_mode))	// 소켓
			str = "socket";
		else
			str = "unknown mode";		// 그 외 나머지

		// 지정된 파일의 종류 출력
		printf("name = %s, type = %s\n", argv[i], str);
	}

	exit(0);
}
