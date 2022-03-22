#include <stdio.h>
#include <stdlib.h>

#define BUFFER_MAX 256

int main(void)
{
	char command[BUFFER_MAX];	// 명령문
	char *prompt = "Prompt>>";	

	while (1) {
		fputs(prompt, stdout);	// 입력마다 프롬프트 출력

		// 프롬프트 입력 없을 시 입력 종료
		if (fgets(command, sizeof(command), stdin) == NULL)
			break;

		system(command);	// 입력된 리눅스 명령어 실행
	}

	fprintf(stdout, "Good bye...\n");	// 표준 출력 버퍼에 문자열 저장
	fflush(stdout);		// 출력 버퍼에 저장된 문자열 모두 출력
	exit(0);
}
