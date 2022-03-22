#include <stdio.h>	// fputs()가 정의된 헤더 파일
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	FILE *fp;

	// 입력된 인자 개수 확인
	if (argc != 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	// 기존 파일 없을 시 생성 후 오픈, 실패 시 에러 처리
	if ((fp = fopen(argv[1], "w+")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", argv[1]);
		exit(1);
	}

	// 키보드로 입력된 데이터를 파일에 쓰기
	fputs("Input String >> ", stdout);
	gets(buf);	// 개행 문자를 포함한 데이터 저장
	fputs(buf, fp);	// 출력 시 개행 적용 없음
	rewind(fp);
	// 파일에 쓴 데이터를 터미널에 출력
	fgets(buf, sizeof(buf), fp);	// 개행 문자를 제외한 데이터 저장
	puts(buf);	// 출력 시 자동 개행 적용

	exit(0);
}
