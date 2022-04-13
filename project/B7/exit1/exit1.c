#include <stdio.h>
#include <unistd.h>

// 프로그램 종료 시 표준 입출력 정리 없음
int main(void)
{
	printf("Good afternoon?");
	_exit(0);
}
