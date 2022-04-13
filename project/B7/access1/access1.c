#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 여러 개의 파일 각각의 존재 여부와 사용자 접근 권한 확인
int main(int argc, char *argv[])
{
	int i;

	// 인자 개수 확인
	if (argc < 2) {
		fprintf(stderr, "usage: %s <file1> <file2>\n", argv[0]);
		exit(1);
	}

	// 입력된 각 파일의 존재 여부 및 파일 접근 권한 검사
	for (i = 1; i < argc; i++) {
		// 파일 존재하지 않으면 에러 처리
		if (access(argv[i], F_OK) < 0) {
			fprintf(stderr, "%s doesn't exist\n", argv[i]);
			continue;
		}

		// 실제 사용자는 파일에 대해 읽기 권한 보유
		if (access(argv[i], R_OK) == 0)
			printf("User can read %s\n", argv[i]);

		// 사용자는 파일에 대해 쓰기 권한 보유
		if (access(argv[i], W_OK) == 0)
			printf("User can write %s\n", argv[i]);

		// 사용자는 파일에 대해 실행 권한 보유
		if (access(argv[i], X_OK) == 0)
			printf("User can execute %s\n", argv[i]);
	}

	exit(0);
}
