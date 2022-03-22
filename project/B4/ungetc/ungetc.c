#include <stdio.h>	// ungetc()가 정의된 표준 입출력 헤더 파일
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
	char operator;		// 연산자 저장
	FILE *fp;		// 오픈한 파일
	char character;		// 읽어온 문자
	int number = 0;		// 정수형으로 변환된 값

	// 파일 읽기 전용으로 오픈
	if ((fp = fopen("ssu_expr.txt", "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", "ssu_expr.txt");
		exit(1);
	}

	while (!feof(fp)) {
		// 문자열을 정수로 변환
		while ((character = fgetc(fp)) != EOF && isdigit(character))
			number = 10 * number + character -48;

		// 변환된 정수값 출력
		fprintf(stdout, " %d\n", number);
		number = 0;	// 다음 정수값 변환용 초기화

		// 연산자는 입력 스트림에서 추출 후 표준 출력
		if (character != EOF) {
			ungetc(character, fp);
			operator = fgetc(fp);
			printf("Operator => %c\n", operator);
		}
	}

	fclose(fp);
	exit(0);
}
