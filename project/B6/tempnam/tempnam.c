#include <stdio.h>
#include <stdlib.h>

// 사용자가 직접 지정한 디렉토리와 접두어로 임시파일 이름 생성
int main(int argc, char *argv[])
{
	char *arg_directory = NULL;	// 임시파일이 생성될 디렉토리
	char *arg_prefix = NULL;	// 지정된 파일 이름 접두어

	// 인자 개수 확인, 개수 안 맞을 시 에러 처리
	if (argc != 3) {
		fprintf(stderr, "usage: %s <directory> <prefix>\n", argv[0]);
		exit(1);
	}

	// 지정한 디렉토리/접두어 없을 시 임시파일 이름에 대한 시스템 기본값 출력
	// 지정한 디렉토리/접두어 있을 시 이를 사용한 임시파일명 생성
	arg_directory = argv[1][0] != ' ' ? argv[1] : NULL;
	arg_prefix = argv[2][0] != ' ' ? argv[2] : NULL;
	printf("created: %s\n", tempnam(arg_directory, arg_prefix));
	exit(0);
}
