#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

// 임시파일 생성, 데이터 저장 및 출력
int main(void)
{
	char buf[BUFFER_SIZE];
	char name[L_tmpnam];
	FILE *fp;

	// 임시파일 이름 출력
	printf("Temporary filename is <<%s>>\n", tmpnam(name));

	// 임시파일 생성
	if ((fp = tmpfile()) == NULL) {
		fprintf(stderr, "tmpfile error\n");
		exit(1);
	}

	fputs("create tmpfile success!!\n", fp); // 임시파일에 데이터 입력
	rewind(fp);		// 오프셋 위치를 파일의 시작점으로 재설정
	fgets(buf, sizeof(buf), fp);	// 임시파일에서 데이터 읽어오기
	fputs(buf, stdout);		// 읽어온 데이터 출력
	exit(0);
}
