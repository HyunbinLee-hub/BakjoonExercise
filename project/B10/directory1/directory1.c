#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define DIRECTORY_SIZE MAXNAMLEN

// 지정된 디렉토리의 하위 파일 출력 및 정규파일 크기 출력
int main(int argc, char *argv[])
{
	struct dirent *dentry;
	struct stat statbuf;
	char filename[DIRECTORY_SIZE+1];
	DIR *dirp;

	// 인자의 개수 점검
	if (argc < 2) {
		fprintf(stderr, "usage: %s <directory>\n", argv[0]);
		exit(1);
	}

	// 디렉토리 오픈 및 현재 작업 디렉토리 변경
	if ((dirp = opendir(argv[1])) == NULL || chdir(argv[1]) < 0) {
		fprintf(stderr, "opendir, chdir error for %s\n", argv[1]);
		exit(1);
	}

	// 디렉토리 내 모든 파일 조회
	while ((dentry = readdir(dirp)) != NULL) {
		// 삭제된 파일은 조회 대상에서 제외
		if (dentry->d_ino == 0)
			continue;

		// 파일명 저장
		memcpy(filename, dentry->d_name, DIRECTORY_SIZE);

		// 파일 정보 불러오기
		if (stat(filename, &statbuf) == -1) {
			fprintf(stderr, "stat error for %s\n", filename);
			break;
		}

		// 정규파일이면 파일명과 파일 크기 모두 출력
		if ((statbuf.st_mode & S_IFMT) == S_IFREG)
			printf("%-14s %ld\n", filename, statbuf.st_size);
		else
			printf("%-14s\n", filename);
	}

	exit(0);
}
