#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

// 파일에 저장된 데이터를 읽어와 지정한 형식으로 다시 저장
int main(void)
{
	char *fname = "ssu_test.dat";
	char name[BUFFER_SIZE];
	FILE *fp;
	int age;

	// 읽기전용으로 오픈 후 파일 내 데이터 읽어오기
	fp = fopen(fname, "r");
	fscanf(fp, "%s%d", name, &age);
	fclose(fp);
	// 쓰기전용으로 다시 오픈 후 지정된 형식으로 파일 데이터 갱신
	fp = fopen(fname, "w");
	fprintf(fp, "%s is %d years old\n", name, age);
	fclose(fp);
	exit(0);
}
