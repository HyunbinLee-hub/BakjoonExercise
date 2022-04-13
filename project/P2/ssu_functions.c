// ssu_sdup.c, ssu_find-md5.c, ssu_find-sha1.c에서 공통으로 사용하는 함수 정의
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ssu_functions.h"

// 명령문 파싱
int parseCmd(char *cmd, char *argv[])
{
	int argc = 0;
	char *ptr = NULL;

	ptr = strtok(cmd, " ");
	while (ptr != NULL) {
		argv[argc++] = ptr;
		ptr = strtok(NULL, " ");
	}

	return argc;
}

// 명령행 인자의 각 문법 점검
// 총 검색시간 출력
void ssu_searchTime(struct timeval *begin_t, struct timeval *end_t)
{
	end_t->tv_sec -= begin_t->tv_sec;

	if (end_t->tv_usec < begin_t->tv_usec) {
		end_t->tv_sec--;
		end_t->tv_usec += SEC_TO_MICRO;
	}
	end_t->tv_usec -= begin_t->tv_usec;

	printf("Searching time: %ld:%06ld(sec:usec)\n\n", end_t->tv_sec, end_t->tv_usec);
}
