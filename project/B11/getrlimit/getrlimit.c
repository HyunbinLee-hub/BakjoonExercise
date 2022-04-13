#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

#define ssu_show(limit) ssu_show_limit(limit, #limit);

// 프로세스에 할당된 자원의 한계값 조회
void ssu_show_limit(int rlim_type, char *rlim_name);

int main(void)
{
	printf("	resource soft limit hard limit	\n\n");
	ssu_show(RLIMIT_CPU);		// 사용 가능한 최대 CPU 시간
	ssu_show(RLIMIT_FSIZE);		// 파일의 최대 크기
	ssu_show(RLIMIT_DATA);		// 자료 구역 전체의 최대 크기
	ssu_show(RLIMIT_STACK);		// 스택의 최대 크기
	ssu_show(RLIMIT_CORE);		// 한 코어 파일의 최대 크기
#ifdef RLIMIT_RSS
	ssu_show(RLIMIT_RSS);		// 메모리 상주 세트 크기
#endif
#ifdef RLIMIT_MEMLOCK
	ssu_show(RLIMIT_MEMLOCK);	// mlock으로 잠금 가능한 메모값리 최대 용량
#endif
#ifdef RLIMIT_NPROC
	ssu_show(RLIMIT_NPROC);		// 실제 사용자 id당 최대 자식 프로세스 개수
#endif
#ifdef RLIMIT_OFILE
	ssu_show(RLIMIT_OFILE);		// RLIMIT_NOFILE과 동일
#endif
#ifdef RLIMIT_NOFILE
	ssu_show(RLIMIT_NOFILE);	// 한 프로세스가 열어둘 수 있는 최대 파일 개수
#endif
#ifdef RLIMIT_VMEN
	ssu_show(RLIMIT_VMEN);		// 총 자유 메모리 용량의 최댓
#endif
	exit(0);
}

void ssu_show_limit(int rlim_type, char *rlim_name)
{
	struct rlimit rlim;
	char cur[11], max[11];

	getrlimit(rlim_type, &rlim);

	if (rlim.rlim_cur == RLIM_INFINITY)	// 자원의 약한 한계값
		strcpy(cur, "infinity");
	else
		sprintf(cur, "%10ld", rlim.rlim_cur);

	if (rlim.rlim_max == RLIM_INFINITY)	// 자원의 강한 한계값
		strcpy(max, "infinity");
	else
		sprintf(max, "%10ld", rlim.rlim_max);

	printf("%15s : %10s %10s\n", rlim_name, cur, max);	// 자원 한계값 출력
}