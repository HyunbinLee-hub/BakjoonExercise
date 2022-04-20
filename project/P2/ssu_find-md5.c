#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
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

int filter(const struct dirent *entry);
void get_md5Hash(char *filename, unsigned char *md);	// 파일로부터 md5 해시값 추출
void put_md5Hash(unsigned char *md);			// 해시값 출력
List setList[LISTMAX];
int setIdx = 0;

int main(int argc, char *argv[])
{
	char *ptr;
	double min, max;
	char dirName[BUFMAX];
	struct stat statbuf;
	struct timeval begin_t, end_t;
	long int size;
	unsigned char *hash;
	List list;
	Node * start;
	Info * pinfo;

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
			minsize = 1;
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
	// 숫자 없이 "~"만 입력된 경우
	if ((max = strtod(argv[3], &ptr)) == 0) {
		if (strcmp(argv[3], "~") == 0) {	// "~" 입력
			maxsize = LONG_MAX;		// long형의 최대치로 설정
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
		sprintf(dirName, "%s/%s%s", "/home", getenv("USER"), ptr+1);
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

	// 지정된 디렉토리의 모든 하위 파일들에 대한 파일 리스트 생성
	// 리스트 내 모든 파일은 명령행 인자의 조건 충족
	ListInit(&list);
	// 리스트에 대한 정렬 규칙 설정
	SetSortRule(&list, sort_identical);

	searchFiles(dirPath, 0, &list);		// 파일 검색

	// 중복 파일 리스트 초기화
	for (int i = 0; i < FILEMAX; i++) {
		ListInit(&setList[i]);
	}
	if (ListFirst(&list, &pinfo)) {
		//get_identicalFiles(&list, setList);
		showFileinfo(pinfo);
		while (ListNext(&list, &pinfo)) {
			//get_identicalFiles(&list, setList);
			showFileinfo(pinfo);
		}
	}

	// 중복 파일 리스트의 각 세트 초기화
	for (int i = 0; i < LISTMAX; i++) {
		ListInit(&setList[i]);
	}
	

	// 중복 파일 리스트가 존재하지 않는 경우
	if (setIdx == 0) {
		printf("No duplicates in %s\n", dirPath);
	}
	else  {	// 중복 파일 리스트가 하나라도 존재하는 경우
		for (int i = 1; i <= setIdx; i++) {
			showFileList(&setList[set_num], i);
		}
	}

	printf("%d\n", ListCount(&list));
	gettimeofday(&end_t, NULL);
	ssu_searchTime(&begin_t, &end_t);	// 전체 검색 시간 출력

	// >> [SET_INDEX] [OPTION ... ] 작업 수행
	while (1) {
		char cmd[BUFMAX];	// 명령문
		int set_num;		// 세트 번호
		int list_num;		// 한 세트 내 파일 번호
		int cnt;		// 명령문 파싱용
		char *token[TOKMAX];
		Info *pinfo;

		memset(cmd, 0, BUFMAX);
		printf(">> ");
		fgets(cmd, BUFMAX, stdin);

		// 입력이 없으면 에러 처리 
		if (strcmp(cmd, "\n") == 0) {
			fprintf(stderr, "usage: [SET_INDEX] [OPTION ... ]\n");
			continue;
		}
		else if (strcmp(cmd, "exit\n") == 0) {
			printf(">> Back to Prompt\n");
			break;
		}
		else
			cmd[strlen(cmd)-1] = '\0';

		// 인자의 개수는 최소 2개 이상
		if ((cnt = parseCmd(cmd, token)) < 2) {
			fprintf(stderr, "usage: [SET_INDEX] [OPTION ... ]\n");
			continue;
		}

		// 첫번째 인자가 인덱스 범위 내 숫자인지 확인
		if ((set_num = atoi(token[0])) <= 0 || set_idx <= setIdx) {
			fprintf(stderr, "set index error\n");
			continue;
		}

		if (strcmp(token[1], "d") == 0) {	// d옵션 설정
			int index = 1;			// 인덱스 번호
			Info rminfo;

			// [LIST_IDX] 에 해당하는 파일 삭제
			if (cnt > 2 && (list_num = atoi(token[2])) > 0 && 
					list_num < ListCount(&setList[set_num])) {
				// 지정한 파일 제거
				if (ListFirst(&setList[set_num], &pinfo)) {
					for (int i = 1; i <= ListCount(&setList[set_num]); i++) {
						// 현재 인덱스 번호가 [LIST_IDX]와 동일
						if (index == list_num) {
							// 중복 파일 리스트에서 삭제
							rminfo = ListRemove(&setList[set_num]);
							// 실제 파일 삭제
							remove(rminfo->path);
							printf(\"%s\" has been deleted in #%d\n", rminfo->path, set_num);
							break;
						}
						else 
							ListNext(&setList[set_num], &pinfo);
					}
				}

				// 중복 리스트 출력	
				showFileList(&setList[set_num], set_num);
			}
			else {
				fprintf(stderr, "list index error\n");
			}
		}
		else if (strcmp(token[1], "t") == 0) {	// t옵션 설정
			int index = 1;
			time_t max_mtime;
			Info * preInfo;		// 직전 파일 정보

			if (cnt == 2) {
				if (ListFirst(&setList[set_num], &pinfo)) {
					// 파일의 mtime 비교
					for (int i = 1; i <= ListCount(&setList[set_num]); i++) {
						if (i == 1) {
							preInfo = pinfo;
							ListNext(&setList[set_num], &pinfo);
							continue;
						}

						// 직전 파일의 mtime과 현재의 mtime 비교
						if (preInfo->mtime > pinfo->mtime) {
							
						}
						else {
							max_mtime = pinfo->mtime;

						}
					}
				}
			}
			else {
				fprintf(stderr, "option t error\n");	
			}
		}
		else if (strcmp(token[1], "i") == 0) {	// i옵션 설정
			if (cnt == 2) { 
				printf("%s\n", token[1]);
			}
			else {
				fprintf(stderr, "option i error\n");	
			}
		}
		else if (strcmp(token[1], "f") == 0) {	// f옵션 설정
			if (cnt == 2) { 
				printf("%s\n", token[1]);
			}
			else {
				fprintf(stderr, "option f error\n");	
			}
		}
		else {
			fprintf(stderr, "option error\n");
		}
	}

	// 파일 리스트에 할당된 메모리 해제
	if (ListFirst(&list, &pinfo)) {
		pinfo = ListRemove(&list);
		free(pinfo);

		while (ListNext(&list, &pinfo)) {
			pinfo = ListRemove(&list);
			free(pinfo);
		}
	}
	exit(0);
}

// 파일 1개의 md5해시값을 구하는 함수
void get_md5Hash(char *filename, unsigned char *md)
{
	MD5_CTX c;
	int i, err=0;
	int fd;					// 읽어올 파일에 대한 파일 디스크립터
	static unsigned char buf[BUFSIZE];	// 읽어올 파일의 데이터
	FILE *IN;

	// 인자로 지정된 파일 오픈
	IN = fopen(filename,"r");
	if (IN == NULL)
	{
		fprintf(stderr, "fopen error for %s\n", filename);
		return;
	}

	fd = fileno(IN);	// 파일 디스크립터 생성
	MD5_Init(&c);		// md5_ctx 구조체 초기화
	for (;;)
	{
		i = read(fd, buf, BUFSIZE);	// BUFSIZE만큼 파일 데이터 패딩
		if (i <= 0) 
			break;
		MD5_Update(&c, buf, (unsigned long)i);	// 패딩된 데이터에 대한 해시값 부여 
	}
	MD5_Final(&(md[0]),&c);	// 해시 추출 결과를 md에 저장
	fclose(IN);
}
void put_md5Hash(unsigned char *md)	// md5 해시값 출력
{
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
		printf("%02x",md[i]);
	}
}
// 중복 파일 리스트 탐색
void get_identicalFiles(List *plist, List *setList)
{
	Info * curInfo;
	Info * nextInfo;

	// 중복 파일 리스트 탐색
	while (ListiNext(&list, &pinfo)) {
		curInfo = 
	}
}
void searchFiles(char *dirpath, int depth, List *plist) 
{
	int count, idx = 0;
	char *ptr;
	char curpath[PATHMAX];		// 현재 경로 저장
	unsigned char md5[HASHMAX];	// md5 해시값 저장용
	Queue listq;			// 너비우선탐색용 큐
	Info *pinfo;			// 리스트에 저장할 파일 정보
	struct stat statbuf;
	struct dirent **namelist;	// 현재 디렉토리 내 하위 파일 리스트
	int start = 0;

	QueueInit(&listq);

	// 시작 디렉토리의 값을 큐에 저장
	pinfo = (Info *)malloc(sizeof(Info));
	strcpy(pinfo->path, dirpath);
	pinfo->depth = depth;
	Enqueue(&listq, pinfo);

	// 현재 큐가 비어 있는지 확인
	while (!QEmpty(&listq)) {
		// 큐에 저장된 가장 오래된 데이터 가져오기
		Info *curInfo = Dequeue(&listq);

		if (access(curInfo->path, F_OK) != 0) {
			// for Linux Permission denied
			if (errno == 13)
				return;
			fprintf(stderr, "access error for %s\n", dirpath);
			exit(1);
		}

		// 디렉토리 내 하위 파일 이름을 사전순 정렬
		if ((count = scandir(curInfo->path, &namelist, NULL, alphasort)) < 0) {
			fprintf(stderr, "scandir error for %s\n", curInfo->path);
			exit(1);
		} 
		else if (count == 0)
			return;

		// 파일 개수만큼 하위 파일 탐색
		for (int i = start; i < count; i++) {
			if (!strcmp(namelist[i]->d_name, ".") ||
					!strcmp(namelist[i]->d_name, ".."))
				continue;

			// 시작 디렉토리가 루트 디렉토리인지 여부에 따른 하위 경로 설정 방식
			if (strcmp(curInfo->path, "/") == 0) {
				if (strcmp(namelist[i]->d_name, "proc") == 0 ||
						strcmp(namelist[i]->d_name, "run") == 0 ||
						strcmp(namelist[i]->d_name, "sys") == 0) {
					continue;
				}
				sprintf(curpath, "%s%s", curInfo->path, namelist[i]->d_name);
			} 
			else {
				sprintf(curpath, "%s/%s", curInfo->path, namelist[i]->d_name);
			}

			// 현재 파일의 정보 가져오기
			if ((lstat(curpath, &statbuf) < 0) && (!access(curpath, F_OK))) {
				fprintf(stderr, "lstat error for %s\n", curpath);
				exit(1);
			}

			// 정규파일인 경우 파일의 크기 및 해시값을 리스트에 저장
			if (S_ISREG(statbuf.st_mode)) {
				// 파일의 크기가 지정된 범위에 해당
				if (statbuf.st_size >= minsize && statbuf.st_size <= maxsize) {
					// 확장자명을 따로 지정한 경우
					if (strcmp(ext, "") != 0) {
						// 파일의 확장자명이 일치하는 경우
						if ((ptr = strrchr(curpath, '.')) != NULL && strcmp(ext, ptr) == 0) {
							// 노드에 파일 데이터 추가
							// 파일 절대경로
							pinfo = (Info *)malloc(sizeof(Info));
							strcpy(pinfo->path, curpath);
							// 해시값 추출
							get_md5Hash(curpath, md5);
							memcpy(pinfo->hash, md5, sizeof(unsigned char) * HASHMAX);
							// 파일 크기
							pinfo->size = statbuf.st_size;
							// 파일 최종 접근, 수정 시간
							pinfo->mtime = statbuf.st_mtime;
							pinfo->atime = statbuf.st_atime;
							// 절대경로의 길이
							pinfo->depth = curInfo->depth + 1;
							
							// 연결리스트에 저장
							ListInsert(plist, pinfo);
						}
					} 
					else { // 확장자명을 따로 지정하지 않은 경우
						get_md5Hash(curpath, md5);
						pinfo = (Info *)malloc(sizeof(Info));
						strcpy(pinfo->path, curpath);
						memcpy(pinfo->hash, md5, sizeof(unsigned char) * HASHMAX);
						pinfo->size = statbuf.st_size;
						pinfo->mtime = statbuf.st_mtime;
						pinfo->atime = statbuf.st_atime;
						pinfo->depth = curInfo->depth + 1;
						ListInsert(plist, pinfo);
					}
				}
			} 
			else if (S_ISDIR(statbuf.st_mode)) {	// 디렉토리인 경우 큐에 추가
				pinfo = (Info *)malloc(sizeof(Info));
				strcpy(pinfo->path, curpath);
				pinfo->depth = curInfo->depth + 1;
				Enqueue(&listq, pinfo);
			} 
			else
				;
			// 동일 파일 내 하위 디렉토리가 다른 하위디렉토리의 절대경로에 연결되는 것 방지
			strcpy(curpath, curInfo->path);
		}
	}
}
// 파일리스트 출력
void showFileList(List *pset, int setnum)
{
	int index = 1;
	Info * pinfo;

	if (ListFirst(&setList[setnum-1], &pinfo)) {
		// 각 중복 파일 리스트의 세트 번호, 파일 크기, 해시값 출력
		printf("--- Identical files #%d (", setnum);
		put_md5Hash(pinfo->hash);
		printf(" bytes - ");
		putCommaToSize(pinfo->size);
		printf(") ----\n");

		// 중복 파일 리스트에 저장된 파일 정보 출력
		printf("[%d] %s (mtime : %s) (atime : %s)\n", index++, pinfo->path, 
				printTime(statbuf.st_mtime), printTime(statbuf.st_atime));
		while (ListNext(&setList[setnum-1], &pinfo)) {
			printf("[%d] %s (mtime : %s) (atime : %s)\n", index++, pinfo->path, 
						printTime(statbuf.st_mtime), printTime(statbuf.st_atime));
		}
	}
}
// 정렬 기준 설정(오름차순)
int sort_identical(LData a, LData b)
{
	// 정렬 우선순위: 파일 크기>해시값>절대경로 길이 순
	if (a->size > b->size)
		return 1;		// 내림차순
	else if (a->size < b->size)
		return -1;		// 오름차순
	else {
		if (strcmp(a->hash, b->hash) > 0)
			return 1;
		else if (strcmp(a->hash, b->hash) < 0)
			return -1;
		else {
			if (a->depth > b->depth)
				return 1;
			else if (a->depth > b->depth)
				return -1;
		}
	}
	return 0;
}
