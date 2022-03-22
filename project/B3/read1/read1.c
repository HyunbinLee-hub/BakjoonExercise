#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"	// employee 구조체가 정의된 헤더 파일

int main(int argc, char *argv[])
{
	struct ssu_employee record;	// 구조체 선언
	int fd;
	int record_num;

	// 필요한 인자들의 입력 여부 확인
	if (argc < 2) {
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	}

	// 읽기 전용으로 오픈
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	// 레코드 번호 입력 시 해당 행의 데이터 읽기 수행
	while (1) {
		printf("Enter record number: ");
		scanf("%d", &record_num);

		if (record_num < 0)	// 입력 종료
			break;

		// 찾는 레코드의 처음으로 이동, 데이터 읽기 수행
		if (lseek(fd, (long)record_num * sizeof(record), SEEK_SET) < 0) {
			fprintf(stderr, "lseek error\n");
			exit(1);
		}
		
		// ssu_employeefile에서 읽어온 정보 출력
		if (read(fd, (char *)&record, sizeof(record)) > 0) {
			printf("Employee : %s	Salary : %d\n", record.name, record.salary);
		}
		else {
			printf("Record %d not found\n", record_num);
		}
	}

	close(fd);
	exit(0);
}
