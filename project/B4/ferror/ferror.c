#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp;	// 오픈한 파일을 가리키는 포인터
	int character;	// 입출력한 문자

	// 필요한 인자 개수 충족 여부 확인
	if (argc != 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		exit(1);
	}

	// 읽기 전용으로 파일 오픈, 실패 시 에러 처리
	if ((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", argv[1]);
		exit(1);
	}

	character = fgetc(fp);	// 첫번째 문자 읽기

	// 한 글자씩 파일 내 모든 데이터 읽기
	while (!feof(fp)) {
		fputc(character, stdout); // 한 글자씩 읽어온 데이터 출력

		// 데이터 출력 중 오류 발생 시 에러 메시지 출력
		if (ferror(fp)) {
			fprintf(stderr, "Error detected!!\n");
			clearerr(fp);	// 에러 초기화 후 다음 문자 출력
		}

		character = fgetc(fp);	// 다음 문자 읽기
	}

	fclose(fp);
	exit(0);
}
