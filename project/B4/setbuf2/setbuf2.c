#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buf[BUFFER_SIZE];
	int a, b;
	int i;

	setbuf(stdin, buf);		// 버퍼링할 입력 버퍼 설정
	scanf("%d %d", &a, &b);		// 각 변수에 데이터 입력
	for (i = 0; buf[i] != '\n'; i++)	
		putchar(buf[i]);	// 개행문자 이전 데이터 한번에 출력
	putchar('\n');
	exit(0);
}
