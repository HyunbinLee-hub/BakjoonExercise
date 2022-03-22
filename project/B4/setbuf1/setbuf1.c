#include <stdio.h>		// setbuf()가 정의된 표준입출력 헤더파일
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024	// 버퍼의 길이

int main(void)
{
	char buf[BUFFER_SIZE];

	setbuf(stdout, buf);	// 설정한 버퍼로 버퍼링
	printf("Hello, ");	// 버퍼링 후 한번에 문자열 출력
	sleep(1);
	printf("OSLAP!!");
	sleep(1);
	printf("\n");		// 개행문자도 버퍼링 대상
	sleep(1);
	setbuf(stdout, NULL);	// 버퍼링 없이 바로 출력
	printf("How");		// 각 printf 함수 호출마다 문자열 출력
	sleep(1);
	printf(" are");
	sleep(1);
	printf(" you?");
	sleep(1);
	printf("\n");

	exit(0);
}
