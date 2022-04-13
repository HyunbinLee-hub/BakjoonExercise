#ifndef FUNCTION_H
#define FUNCTION_H

#define TRUE 1
#define FALSE 0

#define ARGMAX 5		// 명령행 인자의 최대 개수
#define TOKMAX 3		// 삭제 시 명령행 인자의 최대 개수

#define BUFMAX 1024				// 버퍼의 크기
#define BUFSIZE 1024*16				// 한번에 읽어올 파일 데이터의 최대 길이
#define SEC_TO_MICRO 1000000			// 마이크로초 변환
#define FILEMAX 256				// 파일명의 길이
#define PATHMAX 4096				// 경로명의 길이

#define REGFILE 1				// 정규파일
#define DIRECTORY 2				// 디렉토리 파일

// 중복 파일 리스트의 정보
typedef struct node
{
	char path[PATHMAX];
	size_t size;
	int depth;
} fileinfo;

int parseCmd(char *cmd, char *argv[]);
void ssu_searchTime(struct timeval *begin_t, struct timeval *end_t);
void searchDir(char *dirname, int depth, char *ext, long minsize, long maxsize);
int compare_depth(const void *a, const void *b);

//void get_md5Hash(char *filename);
//void calc_md5Hash(FILE *fp);
//void print_md5Hash(unsigned char *md);

#endif
