#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// 사용자가 입력한 대로 표준 출력에 출력하는 프로그램
int main(void)
{
	char buf[BUFFER_SIZE];	// 입력을 저장할 버퍼
	int length;		// null 문자 이전까지 읽어들인 바이트 수

	length = read(0, buf, BUFFER_SIZE);	// 표준 입력의 데이터를 버퍼에 저장
	write(1, buf, length);	// 버퍼에 저장한 데이터 출력
	exit(0);
}
