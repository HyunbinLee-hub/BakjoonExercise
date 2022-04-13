#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 파일 이름 변경
int main(int argc, char *argv[])
{
	// 인자의 개수 점검
	if (argc != 3) {
		fprintf(stderr, "usage: %s <oldname> <newname>\n", argv[0]);
		exit(1);
	}

	// 기존 파일에 대한 새로운 파일의 링크 생성
	if (link(argv[1], argv[2]) < 0) {
		fprintf(stderr, "link error\n");
		exit(1);
	}
	else
		printf("step1 passed.\n");

	// 기존 파일에 대한 링크 해제, 실패 시 모든 파일 삭제
	if (remove(argv[1]) < 0) {
		fprintf(stderr, "remove error\n");
		remove(argv[2]);
		exit(1);
	}
	else
		printf("step2 passed.\n");
	
	printf("Success!\n");
	exit(0);
}
