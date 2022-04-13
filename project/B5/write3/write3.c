#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

// 구조체 단위를 입력한 데이터를 파일에 저장
int main(int argc, char *argv[])
{
	struct ssu_employee record;
	int fd;

	// 인자의 개수 확인
	if (argc < 2) {
		fprintf(stderr, "usage: %s file\n", argv[0]);
		exit(1);
	}

	// 기존 파일이 없으면 새로 생성해서 오픈, 생성 실패 시 에러 처리
	if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) < 0)
	{
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	while (1) {
		printf("Enter employee <SPACE> salary: ");
		scanf("%s", record.name);	// 직원명 입력

		if (record.name[0] == '.')	// 입력 종료 조건
			break;

		scanf("%d", &record.salary);	// 봉급 입력
		record.pid = getpid();		// 직원별 프로세스id 부여
		write(fd, (char *)&record, sizeof(record));
		// 구조체 단위로 파일에 쓰기
	}

	close(fd);
	exit(0);
}
