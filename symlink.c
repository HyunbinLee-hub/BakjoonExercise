#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 심볼릭 링크 생성
int main(int argc, char *argv[])
{
	// 인자의 개수 확인
	if (argc != 3) {
		fprintf(stderr, "usage: %s <actualname> <symname>\n", argv[0]);
		exit(1);
	}

	// 첫번째 파일에 대한 심볼릭 링크 생성, 결과 출력
	if (symlink(argv[1], argv[2]) < 0) {
		fprintf(stderr, "symlink error\n");
		exit(1);		
	}
	else
		printf("symlink: %s -> %s\n", argv[2], argv[1]);

	exit(0);
}
