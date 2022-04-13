#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 4096

// 임시파일 생성 후 데이터 저장 및 출력
int main(void)
{
	char buf[MAX_LINE];
	char name[L_tmpnam];
	FILE *fp;

	// 임시파일 이름 생성 및 출력
	printf("temp file1 : %s\n", tmpnam(NULL));
	tmpnam(name);
	printf("temp file2 : %s\n", name);
	
	// 쓰기 모드로 임시 파일 생성
	if ((fp = tmpfile()) == NULL) {
		fprintf(stderr, "tmpfile error\n");
		exit(1);
	}

	// 아래 문장을 임시파일에 저장, 파일 시작점으로 오프셋 위치 초기화
	fputs("tmpfile created temporary file.\n", fp);
	fseek(fp, 0L, SEEK_SET);

	// 파일에 저장된 데이터를 읽어와서 표준 출력에 출력
	if (fgets(buf, sizeof(buf), fp) == NULL) {
		fprintf(stderr, "fgets error\n");
		exit(1);
	}

	fputs(buf, stdout);
	exit(0);
}
