#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

// 경로의 최대 길이
#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define MAX_PATH_GUESSED 1024

// 명령어의 최대 길이
#ifndef LINE_MAX
#define LINE_MAX 2048
#endif

char *pathname;		// 경로명
char command[LINE_MAX+1], grep_cmd[LINE_MAX];	// 입력, 실행할 명령어
// sprintf 호출 시 경고창 방지를 위해 command의 길이를 예시보다 1 증가시킴

// grep 명령어 실행
int ssu_do_grep(void) {
	struct dirent *dirp;
	struct stat statbuf;
	char *ptr;
	DIR *dp;

	// 지정된 경로에 해당하는 파일 정보 읽기
	if (lstat(pathname, &statbuf) < 0) {
		fprintf(stderr, "lstat error for %s\n", pathname);
		return 0;
	}

	// 읽은 파일이 디렉토리가 아닌 경우 grep 명령어 실행
	if (S_ISDIR(statbuf.st_mode) == 0) {
		sprintf(command, "%s %s", grep_cmd, pathname);
		printf("%s : \n", pathname);
		system(command);
		return 0;
	}

	// 읽은 파일이 디렉토리인 경우
       	// 디렉토리의 하위 파일에 대한 절대경로 생성용 사전 작업 	
	ptr = pathname + strlen(pathname);
	*ptr++ = '/';
	*ptr = '\0';

	// 현재 디렉토리 오픈
	if ((dp = opendir(pathname)) == NULL) {
		fprintf(stderr, "opendir error for %s\n", pathname);
		return 0;
	}

	// 오픈한 디렉토리의 하위 파일 조회
	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, "..")) {
			// 현재 파일의 절대경로 생성
			strcpy(ptr, dirp->d_name);
			// 하위 파일에 대해 재귀
			if (ssu_do_grep() < 0)
				break;
		}
	}

	ptr[-1] = 0;	// 경로명을 가리키는 포인터 초기화
	closedir(dp);	// 디렉토리 닫기
	return 0;
}

// grep 명령어 생성
void ssu_make_grep(int argc, char *argv[]) 
{
	int i;
	strcpy(grep_cmd, " grep");

	// grep 명령문 생성
	for (i = 1; i < argc-1; i++) {
		strcat(grep_cmd, " ");
		strcat(grep_cmd, argv[i]);
	}
}

int main(int argc, char *argv[])
{
	// 인자의 개수 확인
	if (argc < 2) {
		fprintf(stderr, "usage: %s <-CVbchilnsvwx> <-num> <-A num> <-B num> <-f file> \n" "	 <-e> expr <directory>\n", argv[0]);
		exit(1);
	}

	// 경로명의 최대 길이가 0인 경우 
	if (pathmax == 0) {
		if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)
			pathmax = MAX_PATH_GUESSED;
		else
			pathmax++;
	}

	// 경로명을 저장할 메모리가 확보 안 됨
	if ((pathname = (char *) malloc(pathmax+1)) == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}

	// 입력한 경로명으로 grep 명령문 생성 및 실행
	strcpy(pathname, argv[argc-1]);
	ssu_make_grep(argc, argv);
	ssu_do_grep();
	exit(0);
}
