#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 작업 디렉토리 변경
int main(void)
{
	// 지정된 디렉토리로 작업 디렉토리 변경
	if (chdir("/etc") < 0) {
		fprintf(stderr, "chdir error\n");
		exit(1);
	}

	printf("chdir to /etc succeeded\n");
	exit(0);
}
