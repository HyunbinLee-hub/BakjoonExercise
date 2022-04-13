#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ssu_addone(void);			// 지역 범위에서 환경변수 LOVER 추가

extern char **environ;			// 환경변수 리스트
char glob_var[] = "HOBBY=swimming";	// 전역 범위에서 추가할 환경변수

// 환경변수 추가 전후 환경변수 리스트 비교
int main(void)
{
	int i;

	// 작업 전 환경변수 전체 목록 출력
	for (i = 0; environ[i] != NULL; i++)
		printf("environ[%d] : %s\n", i, environ[i]);
	// 환경변수 추가
	putenv(glob_var);
	ssu_addone();
	// 환경변수 값 출력: 환경변수가 정상적으로 리스트에 추가되었는지 확인
	printf("My hobby is %s\n", getenv("HOBBY"));
	printf("My lover is %s\n", getenv("LOVER"));
	// 환경변수 값 변경
	strcpy(glob_var+6, "swimming");

	// 작업 후 환경변수 전체 목록 출력
	for (i = 0; environ[i] != NULL; i++)
		printf("environ[%d] : %s\n", i, environ[i]);
	exit(0);
}

void ssu_addone(void)
{
	char auto_var[10];
	strcpy(auto_var, "LOVER=js");
	putenv(auto_var);	// 환경변수 추가
}
