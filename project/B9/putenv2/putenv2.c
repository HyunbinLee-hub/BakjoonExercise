#include <stdio.h>
#include <stdlib.h>

void ssu_printenv(char *label, char ***envpp);

extern char **environ;

// 지역변수로 선언된 환경변수 등록 및 출력
int main(int argc, char *argv[], char *envp[])
{
	// 환경변수 등록 전 초기 환경변수 목록
	ssu_printenv("Initially", &envp);
	// 환경변수 TZ의 값 변경 후 환경변수 목록 출력
	putenv("TZ=PST8PDT");
	ssu_printenv("After changing TZ", &envp);
	// 환경변수 WARNING 추가 후 목록 출력
	putenv("WARNING=Don't use envp after putenv()");
	ssu_printenv("After setting a new variable", &envp);
	// 환경변수 WARNING의 값 출력
	printf("value of WARNING is %s\n", getenv("WARNING"));
	exit(0);
}

void ssu_printenv(char *label, char ***envpp)
{
	char **ptr;

	// 환경변수 목록 출력	
	printf("---- %s ---\n", label);
	printf("envp is at %8o and contains %8o\n", envpp, *envpp);
	printf("environ is at %8o and contains %8o\n", &environ, environ);
	printf("My environment variable are:\n");

	for (ptr = environ; *ptr; ptr++)
		printf("(%8o) = %8o -> %s\n", ptr, *ptr, *ptr);

       	printf("(%8o) = %8o\n", ptr, *ptr);
}
