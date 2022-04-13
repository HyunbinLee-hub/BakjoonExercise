#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <openssl/md5.h>
#include "ssu_functions.h"

char *ext;		// 추출한 파일 확장자명
long int minsize;
long int maxsize;
char dirPath[BUFMAX];	// [TARGET_DIRECTORY]의 절대경로
int d_option, i_option, f_option, t_option;

void get_md5Hash(char *filename);			// 파일로부터 md5 해시값을 얻어오는 함수
void calc_md5Hash(FILE *fp);				// 해시값 추출
void put_md5Hash(unsigned char *md);			// 해시값 출력

int main(int argc, char *argv[])
{
	char *ptr;
	double min, max;
	char dirName[BUFMAX];
	struct stat statbuf;
	struct timeval begin_t, end_t;

	// [FILE_EXTENSION] 인자 점검
	if (argv[1][0] == '*') {
		if (strlen(argv[1]) == 1) {	// "*"만 입력
			ext = argv[1] + 1;
		}
		else if (argv[1][1] == '.' && strlen(argv[1]) > 2) { // "*.(확장자명)"
			ext = argv[1] + 1;
		}
		else {	// 입력된 것이 "*."나 "*asdsds" 같은 경우
			fprintf(stderr, "file extension error\n");
			exit(1);
		}	
	}
	else {	// "*"나 "*.(확장자명)" 이외의 입력
		fprintf(stderr, "file extension error\n");
		exit(1);
	}

	// [MINSIZE] 인자 점검
	// 실수로 변환할 숫자가 없는 경우
	if ((min = strtod(argv[2], &ptr)) == 0) {
		if (strcmp(argv[2], "~") == 0) {	// "~" 입력
			minsize = 0;
		}
		else {	// "~" 외 다른 문자열 입력
			fprintf(stderr, "minsize error!\n");
			exit(1);
		}
	}
	else if (strcmp(ptr, "\0") != 0) {	// 실수 변환 후 문자열 존재
		if (strcmp(ptr, "KB") == 0 || strcmp(ptr, "kb") == 0)	// KB 단위 byte 변환
		{
			min *= 1024;
		}
		else if (strcmp(ptr, "MB") == 0 || strcmp(ptr, "mb") == 0)	// MB단위 byte 변환
		{
			min *= 1024*1024;
		}
		else if (strcmp(ptr, "GB") == 0 || strcmp(ptr, "gb") == 0)	// GB단위 byte 변환
		{
			min *= 1024*1024*1024;
		}
		else {
			fprintf(stderr, "minsize error\n");
			exit(1);
		};
		minsize = (long)min;
	}
	else
		minsize = (long)min;

	// [MAXSIZE] 인자 점검
	if ((max = strtod(argv[3], &ptr)) == 0) {
		if (strcmp(argv[3], "~") == 0) {	// "~" 입력
			maxsize = LONG_MAX;
		}
		else {	// "~" 외 다른 문자열 입력
			fprintf(stderr, "maxsize error!\n");
			exit(1);
		}
	}
	else if (strcmp(ptr, "\0") != 0) {	// 실수 변환 후 문자열 존재
		if (strcmp(ptr, "KB") == 0 || strcmp(ptr, "kb") == 0)	// KB 단위 byte 변환
		{
			max *= 1024;
		}
		else if (strcmp(ptr, "MB") == 0 || strcmp(ptr, "mb") == 0)	// MB단위 byte 변환
		{
			max *= 1024*1024;
		}
		else if (strcmp(ptr, "GB") == 0 || strcmp(ptr, "gb") == 0)	// GB단위 byte 변환
		{
			max *= 1024*1024*1024;
		}
		else {
			fprintf(stderr, "maxsize error\n");
			exit(1);
		}
		maxsize = (long)max;
	}
	else {
		maxsize = (long)max;
	}

	// minsize가 maxsize보다 큰 경우 에러 처리
	if (minsize > maxsize) {
		fprintf(stderr, "minsize must not be bigger than maxsize\n");
		exit(1);
	}

	// [TARGET_DIRECTORY] 인자 점검
	if ((ptr = strstr(argv[4], "~")) != NULL) {	// "~(홈 디렉토리)"를 포함한 경로인 경우
		sprintf(dirName, "%s%s", getenv("HOME"), ptr+1);
	}
	else {
		ptr = argv[4];
		strcpy(dirName, ptr);
	}
	// 입력한 경로를 절대경로로 변환, 실제로 유효한 경로가 아니면 에러 처리
	if (realpath(dirName, dirPath) == NULL) {
		fprintf(stderr, "%s is not exist\n", dirPath);
		exit(1);
	}
	// 입력한 경로의 파일이 디렉토리인지 확인
	if (lstat(dirPath, &statbuf) < 0) {
		fprintf(stderr, "lstat error for %s\n", dirPath);
		exit(1);
	}
	if (!S_ISDIR(statbuf.st_mode)) {
		fprintf(stderr, "Path is not directory\n");
		exit(1);
	}

	// 검색 시간 측정
	gettimeofday(&begin_t, NULL);

	searchDir(dirPath, 0, ext, minsize, maxsize);
	
	gettimeofday(&end_t, NULL);
	ssu_searchTime(&begin_t, &end_t);

	// >> [SET_INDEX] [OPTION ... ] 작업 수행
	while (1) {
		char cmd[BUFMAX];
		int setIdx;
		int listIdx;
		int count;
		char *token[TOKMAX];

		memset(cmd, 0, BUFMAX);
		printf(">> ");
		fgets(cmd, BUFMAX, stdin);

		// Enter만 입력 혹은 exit 입력
		if (strcmp(cmd, "\n") == 0) {
			continue;
		}
		else if (strcmp(cmd, "exit\n") == 0) {
			printf(">> Back to Prompt\n");
			break;
		}
		else
			cmd[strlen(cmd)-1] = '\0';

		// 인자의 개수는 최소 2개 이상
		if ((count = parseCmd(cmd, token)) < 2) {
			fprintf(stderr, "usage: [SET_INDEX] [OPTION ... ]\n");
			continue;
		}

		// 첫번째 인자가 인덱스 범위 내 숫자인지 확인
		if ((setIdx = atoi(token[0])) < 0) {
			fprintf(stderr, "set index error\n");
			continue;
		}

		if (strcmp(token[1], "d") == 0) {
			if ((listIdx = atoi(token[2])) != -1) {
				
			}
			else {
				fprintf(stderr, "list index error\n");
				continue;
			}
		}
		else if (strcmp(token[1], "i") == 0) {
		}
		else if (strcmp(token[1], "f") == 0) {
		}
		else if (strcmp(token[1], "t") == 0) {
		}
		else {
			fprintf(stderr, "option error\n");
		}

		d_option = i_option = f_option = t_option = FALSE;
	}

	exit(0);
}

// 파일 1개의 해시값을 구하는 함수
void get_md5Hash(char *filename)
{
	int i, err=0;
	FILE *IN;

	IN = fopen(filename,"r");
	if (IN == NULL)
	{
		perror(filename);
		err++;
	}
	calc_md5Hash(IN);	// 해시값 추출 함수
	fclose(IN);
	return;
}
void calc_md5Hash(FILE *fp)	// 파일 데이터로 md5 해시값 추출
{
	MD5_CTX c;
	unsigned char md[MD5_DIGEST_LENGTH];	// 16byte = 128비트의 최종 해시값
	int fd;					// 읽어올 파일에 대한 파일 디스크립터
	int i;
	static unsigned char buf[BUFSIZE];	// 읽어올 파일의 데이터

	fd = fileno(fp);	// 파일 디스크립터 생성
	MD5_Init(&c);		// md5_ctx 구조체 초기화
	for (;;)
	{
		i = read(fd, buf, BUFSIZE);	// BUFSIZE만큼 파일 데이터 패딩
		if (i <= 0) 
			break;
		MD5_Update(&c, buf, (unsigned long)i);	// 패딩된 데이터에 대한 해시값 부여 
	}
	MD5_Final(&(md[0]),&c);	// 해시 추출 결과를 md에 저장
	put_md5Hash(md);	// 구한 해시값 출력
	return;
}
void put_md5Hash(unsigned char *md)	// md5 해시값 출력
{
	int i;

	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
		printf("%02x",md[i]);
}

// 파일 탐색 함수
void searchDir(char *dirname, int depth, char *ext, long minsize, long maxsize) 
{
	int count1, count2;
	char *ptr;
	char pathname[PATHMAX];
	struct stat statbuf;
	struct dirent** namelist;
	int subDirIndex[BUFMAX];
	int idx = 0;

	// 인자로 사용된 디렉토리 파일의 존재 여부 확인
	if (access(dirname, F_OK) != 0) {
		// for Linux Permission denied
		fprintf(stderr, "access error for %s\n", dirname);
		exit(1);
	}

	// 디렉토리 존재 시 하위 파일 알파벳순 정렬
	if ((count1 = scandir(dirname, &namelist, NULL, alphasort)) <= 0) {
		fprintf(stderr, "scandir error for %s\n", dirname);
		exit(1);
	}

	// 파일 개수만큼 하위 파일 탐색
	// 정렬된 namelist가 bfs에서의 queue의 역할 담당

	for (int i = 0; i < count1; i++) {
		if (!strcmp(namelist[i]->d_name, ".") || !strcmp(namelist[i]->d_name, ".."))
			continue;

		if (!strcmp(dirname, "/")) {
			if (strcmp(namelist[i]->d_name, "proc") == 0 || strcmp(namelist[i]->d_name, "run") == 0 || strcmp(namelist[i]->d_name, "sys") == 0) {
				continue;
			}
			sprintf(pathname, "%s%s", dirname, namelist[i]->d_name);
		}
		else {
			sprintf(pathname, "%s/%s", dirname, namelist[i]->d_name);
		}

		if ((lstat(pathname, &statbuf) < 0) && (!access(pathname, F_OK))) {
			fprintf(stderr, "lstat error for %s\n", pathname);
			exit(1);
		}

		// 정규파일인 경우 파일의 크기 및 해시값 정보 출력
		if (S_ISREG(statbuf.st_mode)) {
			// 확장자명을 따로 지정한 경우
			if (strcmp(ext, "\0") != 0) {
				if ((ptr = strrchr(pathname, '.')) != NULL && strcmp(ext, ptr) == 0) {
					if (statbuf.st_size >= minsize && statbuf.st_size <= maxsize) {
						printf("%s : ", pathname);
						get_md5Hash(pathname);
						printf(", %ld, %d\n", statbuf.st_size, depth);
					}
				}
			}
			else {	// 확장자명을 따로 지정하지 않은 경우
				if (statbuf.st_size >= minsize && statbuf.st_size <= maxsize) {
					printf("%s : ", pathname);
					get_md5Hash(pathname);
					printf(", %ld, %d\n", statbuf.st_size, depth);
				}
			}
		}
		else if (S_ISDIR(statbuf.st_mode)) {
			subDirIndex[idx++] = i;
		}
		else
			continue;
	}

	for (int i = idx-1; i >= 0; i--) {
		int j;
	       	j = subDirIndex[i];
		if (strcmp(dirname, "/") == 0)
			sprintf(pathname, "%s%s", dirname, namelist[j]->d_name);
		else
			sprintf(pathname, "%s/%s", dirname, namelist[j]->d_name);
		searchDir(pathname, depth+1, ext, minsize, maxsize);
		//printf("%s\n", pathname);
	}

	for (int i = 0; i < count1; i++)
		free(namelist[i]);
	free(namelist);
}

// 리스트 정렬 기준
int compare_depth(const void* a, const void* b)
{
	if (((fileinfo *)a)->depth > ((fileinfo *)b)->depth)
		return 1;
	else if (((fileinfo *)a)->depth < ((fileinfo *)b)->depth)
		return -1;
	else {
		if (strcmp(((fileinfo *)a)->path, ((fileinfo *)b)->path) > 0)
			return 1;
		else if(strcmp(((fileinfo *)a)->path, ((fileinfo *)b)->path) < 0)
			return -1;
	}
	return 0;
}
