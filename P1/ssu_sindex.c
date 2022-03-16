#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "ssu_sindex.h"

char fileName[FILE_MAX];	// FILENAME 인자로 입력한 파일명
char filePath[PATH_MAX];	// FILENAME 인자에 해당하는 파일의 절대경로
char startPath[PATH_MAX];	// 입력한 시작 경로

// 프롬프트 출력 및 명렁어 find, exit, help 실행하는 함수
void ssu_sindex(void)
{
	char command[CMD_LEN] = {0, };
	char *tokens[TOKEN_CNT] = {NULL, };
	int token_cnt;
	char *ptr;
	FILE *fp1, *fp2;

	while (1) {
		// 프롬프트 출력 및 명령어 입력
		printf("20181224> ");
		fgets(command, sizeof(command), stdin);
		// 엔터키만 입력한 경우: 프롬프트 재출력
		if (strcmp(command, "\n") == 0) {
			command[strlen(command)-1] = '\0';
			continue;
		}
		command[strlen(command)-1] = '\0';

		// 입력한 명령어에서 문자열 파싱
		ptr = strtok(command, " \n");
		token_cnt = 0;
		while (ptr != NULL) {
			tokens[token_cnt] = ptr;
			token_cnt++;
			ptr = strtok(NULL, " \n");
		}

		if (strcmp(tokens[0], "find") == 0) {	// find 명령어 실행
			// FILENAME, PATH 입력 여부 점검
			if (token_cnt < 3) {
				fprintf(stderr, "Usage: find [FILENAME] [PATH]\n");
				continue;
			}
			// FILENAME, PATH의 존재 여부 확인
			strcpy(fileName, tokens[1]);		// 파일명만 비교용
			realpath(tokens[1], filePath);		// 파일 경로 비교용
			if ((fp1 = fopen(filePath, "r")) == NULL) {
				fprintf(stderr, "%s is not exist\n", filePath);
				continue;
			}
			realpath(tokens[2], startPath);
			if ((fp2 = fopen(startPath, "r")) == NULL) {
				fprintf(stderr, "%s is not exist\n", startPath);
				continue;
			}
			printf("%s %s %s\n", fileName, filePath, startPath);
			sindex_find(fileName, startPath);

			fclose(fp1);
			fclose(fp2);
		}
		else if (strcmp(tokens[0], "exit") == 0) {	// exit 명령어 실행
			puts("Prompt End");
			return;
		}
		else {	// help 및 기타 명령어 실행
			sindex_help();
		}
	}
}
// help 명령어 수행 함수
void sindex_help(void)
{
	printf("Usage:\n");
	printf("    > find [FILENAME] [PATH]\n");
	printf("\t>> [INDEX] [OPTION]\n");
	printf("    > help\n");
	printf("    > exit\n\n");
	printf("    [OPTION ... ]\n");
	printf("     q : report only when files differ\n");
	printf("     s : report when two files are the same\n");
	printf("     i : ignore case differences in file contents\n");
	printf("     r : recursively compare any subdirectories found\n");
	return;
}
// find 명령어 수행 함수
void sindex_find(char *filename, char *pathname)
{
	struct stat statbuf;
	off_t size = 0;
	char curDir[PATH_MAX];	// 현재 디렉토리 경로
	int depth = 0;
	int index = 0;
	char subCmd[CMD_LEN];
	List list;
	Info * pinfo;

	lstat(filename, &statbuf);
	// 리스트 초기화
	ListInit(&list);
	
	// [FILENAME]의 파일을 [PATH]를 시작디렉토리로 하여 탐색
	if (S_ISDIR(statbuf.st_mode)) {
		realpath(filePath, curDir);
		size = sizeOfDir(curDir, depth, &size);
		searchFiles(&list, pinfo, &size, curDir, depth);
	}
	else {
		size = statbuf.st_size;
		//strcpy(curDir, pathname);
		searchFiles(&list, pinfo, &size, pathname, depth);
	}

	// 리스트 출력
	printf("%5s %4s %-10s %-6s %-5s %-4s %-4s %-16s  %-16s  %-16s  %-30s",
			"Index", "Size", "Mode", "Blocks", "Links", "UID", "GID", "Access", "Change", "Modify", "Path");
	if (ListFirst(&list, &pinfo)) {
		printf("%-5d ", index++);
		show_fileInfo(&list, pinfo);

		while (ListNext(&list, &pinfo)) {
			printf("%-5d ", index++);
			show_fileInfo(&list, pinfo);
		}
	}

	if (list.numOfData < 2) {
		printf("(None)\n");
	}
	else {
		while (1) {
			printf(">> ");
			fgets(subCmd, sizeof(subCmd), stdin);
        	        // 엔터키만 입력한 경우: 프롬프트 재출력
	                if (strcmp(subCmd, "\n") != 0 && atoi(subCmd)) {
                        	subCmd[strlen(subCmd)-1] = '\0';
                        	break;
                	}
		}
	}

	// 전체 작업 종료 후 저장된 리스트 모두 삭제
	if (ListFirst(&list, &pinfo)) {
		pinfo = ListRemove(&list);
		free(pinfo);

		while (ListNext(&list, &pinfo)) {
			pinfo = ListRemove(&list);
			free(pinfo);
		}
	}
	return;
}

long int sizeOfDir(char *curDir, int depth, off_t *psum) 
{
	struct dirent *entry;
	struct stat statbuf;
	DIR *dir;
	char newPath[PATH_MAX];
	int len;
	int fd;

	if ((dir = opendir(curDir)) == NULL || chdir(curDir) < 0) {
		fprintf(stderr, "opendir, chdir error for %s\n", curDir);
		exit(1);
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		len = snprintf(newPath, sizeof(newPath)-1, "%s/%s", curDir, entry->d_name);
		newPath[len] = 0;
		if (entry->d_type == DT_DIR) {
			*psum = sizeOfDir(newPath, depth+1, psum);
		}
		else if (entry->d_type == DT_REG) {
			if ((fd = open(entry->d_name, O_RDONLY)) < 0) {
				fprintf(stderr, "open error for %s\n", newPath);
				continue;
			}
			if (lstat(entry->d_name, &statbuf) == 0) {
				*psum += statbuf.st_size;
			}
			close(fd);
		}
	}

	closedir(dir);
	chdir("..");
	return *psum;
}
// find 명령어 세부작업 1: 입력한 파일명에 해당하는 파일 검색
void searchFiles(List * plist, Info * pinfo, off_t *psize, char *path, int depth)
{
	DIR *dir;
	struct dirent **nameList;
	struct stat statbuf;
	char curDir[PATH_MAX];
	int nameCount;		 
	int idx = 0;		// nameList의 인덱스 번호
	
	realpath(path, curDir);
	// 파일 오픈
	if ((dir = opendir(curDir)) == NULL) {
		fprintf(stderr, "opendir error for %s\n", curDir);
	        return;
	}
	// 현재 디렉토리의 전체 파일 목록 불러오기(알파벳순 정렬)
	if ((nameCount = scandir(curDir, &nameList, NULL, alphasort) < 0))
	{
		fprintf(stderr, "%s: readdir error and scandir error\n", curDir);
	        return;
	}

	// 파일 탐색
	while (nameList[idx] = readdir(dir))
	{
		char newPath[PATH_MAX];
		int len;
		// 절대 경로로 변환
		len = snprintf(newPath, sizeof(newPath)-1, "%s/%s", curDir, nameList[idx]->d_name);
		newPath[len] = 0;
		// 정규 파일인 경우
		if (nameList[idx]->d_type == DT_REG) {
			lstat(fileName, &statbuf);
			if (!S_ISREG(statbuf.st_mode))
				continue;
			// 상대경로/절대경로가 동일한 파일인 경우
			if (strcmp(fileName, nameList[idx]->d_name) == 0 || strcmp(filePath, newPath) == 0) {
				// 경로 추가
                        	len = snprintf(newPath, sizeof(newPath)-1, "%s/%s", curDir, nameList[idx]->d_name);
				newPath[len] = 0;
				// 리스트에 추가
				if (*psize == statbuf.st_size) { 
					pinfo = (Info *)malloc(sizeof(Info));
					init_fileInfo(pinfo, newPath, *psize);
					ListInsert(plist, pinfo);
					break;
				}
			}
		}
		else if (nameList[idx]->d_type == DT_DIR) {	// 디렉토리 파일인 경우
			lstat(filePath, &statbuf);
			// 현재 디렉토리를 경로에 추가
			len = snprintf(newPath, sizeof(newPath)-1, "%s/%s", curDir, nameList[idx]->d_name);
			newPath[len] = 0;
			if (strcmp(nameList[idx]->d_name, ".") == 0 || strcmp(nameList[idx]->d_name, "..") == 0)
                                continue;
			if (S_ISDIR(statbuf.st_mode)) {
				if (*psize == statbuf.st_size) {
					pinfo = (Info *)malloc(sizeof(Info));
					init_fileInfo(pinfo, newPath, *psize);
					ListInsert(plist, pinfo);
					break;
				}
			}
		   	searchFiles(plist, pinfo, psize, newPath, depth+1);	// 재귀를 통한 깊이우선탐색
               	}

	} 
	closedir(dir);	// 파일 탐색 종료 후 디렉토리 닫음
}

// find 명령어 세부작업 2: 검색한 파일 속성 정보 출력
// 리스트에 저장할 파일 속성 정보
int init_fileInfo(Info * pinfo, char *file, long int size)
{
	struct stat buf;
	long int sum = 0;
	int depth = 0;

	// 현재 파일 정보 불러오기
	if (lstat(file, &buf) < 0) {
		fprintf(stderr, "%s's fileinfo error\n", file);
		return FALSE;
	}

	// 파일 크기 정보 불러오기: 디렉토리면 하위 정규 파일들의 합 저장
	if (S_ISDIR(buf.st_mode))
		pinfo->size = size;
	else
		pinfo->size = buf.st_size;
	pinfo->modes = buf.st_mode;		// 파일 종류 및 접근 권한
	pinfo->blockCnt = buf.st_blocks;	// 할당된 블록 수
	pinfo->linkCnt = buf.st_nlink;		// 하드링크 개수
	pinfo->uid = buf.st_uid;		// 사용자 ID
	pinfo->gid = buf.st_gid;		// 그룹 ID
	pinfo->access = buf.st_atime;		// 최종 접근 시간
	pinfo->change = buf.st_ctime;		// 최종 상태 변경 시간
	pinfo->modify = buf.st_mtime;		// 최종 수정 시간
	realpath(file, pinfo->path);		// 파일의 절대 경로
	return TRUE;
}
// 디렉토리 내 모든 파일의 크기 구하기

// 파일 속성 중 파일 접근권한 정보 출력
void show_permission(mode_t * pmode)
{
	char permission[11];

	// 파일 유형 정보
	if (S_ISDIR(*pmode))
		permission[0] = 'd';
	else if (S_ISCHR(*pmode))
		permission[0] = 'c';
	else if (S_ISLNK(*pmode))
		permission[0] = 'l';
	else if (S_ISFIFO(*pmode))
		permission[0] = 'p';
	else if (S_ISBLK(*pmode))
		permission[0] = 'b';
	else if (S_ISSOCK(*pmode))
		permission[0] = 's';
	else
		permission[0] = '-';

	// 사용자 읽기, 쓰기, 실행 권한
	if (*pmode & S_IRUSR)
		permission[1] = 'r';
	else
		permission[1] = '-';
	if (*pmode & S_IWUSR)
		permission[2] = 'w';
	else
		permission[2] = '-';
	if (*pmode & S_IXUSR)
		permission[3] = 'x';
	else
		permission[3] = '-';
		
	// 그룹 읽기, 쓰기, 실행 권한
	if (*pmode & S_IRUSR)
		permission[4] = 'r';
	else
		permission[4] = '-';
	if (*pmode & S_IWUSR)
		permission[5] = 'w';
	else
		permission[5] = '-';
	if (*pmode & S_IXUSR)
		permission[6] = 'x';
	else
		permission[6] = '-';
		
	// 기타 읽기, 쓰기, 실행 권한
	if (*pmode & S_IRUSR)
		permission[7] = 'r';
	else
		permission[7] = '-';
	if (*pmode & S_IWUSR)
		permission[8] = 'w';
	else
		permission[8] = '-';
	if (*pmode & S_IXUSR)
		permission[9] = 'x';
	else
		permission[9] = '-';

	permission[10] = '\0';

	// 파일 접근 권한 출력
	printf("%s ", permission);
}
// 리스트에 저장할 파일 접근 권한 출력
void show_fileInfo(List * plist, Info * pinfo)
{
	printf("%-4ld ", pinfo->size);
	show_permission(&pinfo->modes);
	printf("%-6ld %-5ld %-4d %-4d ", pinfo->blockCnt, pinfo->linkCnt, pinfo->uid, pinfo->gid);
	printTime(&pinfo->access);
	printTime(&pinfo->change);
	printTime(&pinfo->modify);
	printf("%-s\n", pinfo->path);
}
// 파일 최종 접근 시간, 변경 시간, 수정 시간 정보 출력용
void printTime(time_t * ptime)
{
	struct tm * t;
	t = localtime(ptime);
	printf("%04d-%02d-%02d %02d:%02d  ",
		       	(t->tm_year)+1900, (t->tm_mon)+1, t->tm_mday, t->tm_hour, t->tm_min);
}

// 리스트 관련 함수
// 리스트 초기화
void ListInit(List * plist)
{
	plist->head = (Node *)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->numOfData = 0;
}
// 리스트 노드 추가
void ListInsert(List * plist, LData data)
{
	Node * newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head->next;
	plist->head->next = newNode;
	(plist->numOfData)++;	
}
// 탐색 시작할 리스트 노드의 데이터 불러오기
int ListFirst(List * plist, LData * pdata)
{
	if (plist->head->next == NULL)
		return FALSE;

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;
	return TRUE;
}
// 다음에 탐색할 노드의 데이터 불러오기
int ListNext(List * plist, LData * pdata)
{
	if (plist->cur->next == NULL)
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return TRUE;
}
// 리스트 노드 삭제
LData ListRemove(List * plist)
{
	Node * rmPos  = plist->cur;
	LData rmData = rmPos->data;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rmPos);
	(plist->numOfData)--;
	return rmData;
}
// 리스트 노드 개수 리턴
int ListCount(List * plist)
{
	return plist->numOfData;
}
