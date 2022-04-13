#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TABLE_SIZE sizeof(table)/sizeof(*table)

// 파일의 존재 여부 및 접근 권한에 관한 구조체로 access() 호출
int main(int argc, char *argv[])
{
	// 파일 존재 여부 및 접근 권한 관련 구조체
	struct {
		char *text;
		int mode;
	} table[] = {
		{"exists", 0},
		{"execute", 1},
		{"write", 2},
		{"read", 4}
	};
	int i;

	// 인자의 개수 확인
	if (argc < 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(1);
	}

	// 한 파일의 존재 여부 및 사용자 접근 권한 검사
	for (i = 0; i < TABLE_SIZE; i++) {
		if (access(argv[1], table[i].mode) == 0)
			printf("%s -ok\n", table[i].text);
		else
			printf("%s\n", table[i].text);
	}

	exit(0);
}
