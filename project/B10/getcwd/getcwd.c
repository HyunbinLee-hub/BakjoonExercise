#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PATH_MAX 1024	// 경로명의 길이

// 
int main(void)
{
	char *pathname;

	// 작업 디렉토리를 user 디렉토리로 변경
	if (chdir("/home/user") < 0) {
		fprintf(stderr, "chdir error\n");
		exit(1);
	}

	// 경로명을 저장할 메모리 할당
	pathname = malloc(PATH_MAX);

	// 현재 작업 디렉토리 경로 불러오기
	if (getcwd(pathname, PATH_MAX) == NULL) {
		fprintf(stderr, "getcwd error\n");
		exit(1);
	}

	// 현재 작업 디렉토리 경로명 출력
	printf("current directory = %s\n", pathname);
	exit(0);
}
