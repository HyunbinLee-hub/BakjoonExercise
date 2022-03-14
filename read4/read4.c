#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TABLE_SIZE 128		// 구조체 테이블의 길이
#define BUFFER_SIZE 1024	// 버퍼의 길이

int main(int argc, char *argv[])
{
	static struct {
		long offset;
		int length;
	} table[TABLE_SIZE];	// 구조체 배열 선언
	char buf[BUFFER_SIZE];
	long offset;		// 파일의 현재 오프셋
	int entry;		// 구조체 배열의 현재 인덱스
	int length;		// 한 줄의 길이
	int i;
	int fd;

	// 필요한 인자의 개수 확인
	if (argc < 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(1);
	}

	// 읽기 전용으로 파일 오픈, 실패 시 에러
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	// 파일의 처음부터 읽기, 구조체 배열의 처음부터 데이터 저장
	entry = 0;
	offset = 0;
	while ((length = read(fd, buf, sizeof(buf))) > 0)
       	{
		// 구조체 배열에 현재 파일 길이, 오프셋 저장
		for (i = 0; i < length; i++) {
			table[entry].length++;
			offset++;
			
			// 파일의 줄 변경 시 인덱스 번호 증가
			if (buf[i] == '\n')
				table[++entry].offset = offset;
		}
	}

#ifdef DEBUG	// 디버깅 시 구조체 배열에 저장된 파일 오프셋, 길이 정보 출력
	for (i = 0; i < TABLE_SIZE; i++)
		printf("%d : %ld, %d\n", i + 1, table[i].offset, table[i].length);
#endif

	while (1) {
		printf("Enter line number : ");		// 줄 번호 입력
		scanf("%d", &length);

		if (--length < 0)	// 줄 번호 = 배열 인덱스-1, 종료 조건
			break;

		// 파일 한 줄의 길이만큼 문자열로 저장
		lseek(fd, table[length].offset, 0);

		if (read(fd, buf, table[length].length) <= 0)
			continue;

		buf[table[length].length] = '\0';	// 문자열 형태로 버퍼 저장
		printf("%s", buf);			// 버퍼의 데이터 출력
	}

	close(fd);
	exit(0);
}
