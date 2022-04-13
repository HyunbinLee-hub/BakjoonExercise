#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register);

static jmp_buf glob_buffer;

// 함수 경계를 넘나드는 분기 수행
int main(void)
{
	register int loc_register;	// 레지스터 변수
	volatile int loc_volatile;	// 항상 메모리에 접근하는 변수
	int loc_var;			// 지역변수->메모리 스택 영역에 할당

	loc_var = 10;
	loc_volatile = 11;	// 메모리에 직접 저장되어 휘발성 있음->setjmp()을 통한 보존 불가
	loc_register = 12;

	// 현재까지의 지역변수, 레지스터 변수 값을 환경변수에 저장
	if (setjmp(glob_buffer) != 0) {
		printf("after longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n", loc_var, loc_volatile, loc_register);
		exit(0);
	}

	// longjmp() 호출되지 않을 시 각 변수의 값 갱신 및 출력
	loc_var = 80;
	loc_volatile = 81;
	loc_register = 83;
	ssu_nested_func(loc_var, loc_volatile, loc_register);

	exit(0);
}

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register)
{
	printf("before longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n", loc_var, loc_volatile, loc_register);
	longjmp(glob_buffer, 1);	// setjmp()에서 저장된 이전의 지역변수, 레지스터 변수값 사용
}