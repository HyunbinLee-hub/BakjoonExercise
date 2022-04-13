#include <stdio.h>
#include <stdlib.h>

// 해적 인적사항
struct ssu_pirate {
	unsigned long booty;
	unsigned int beard_length;
	char name[128];
};

// 구조체에 저장된 정보를 파일에 쓰기 후 다시 읽어와서 출력
int main(void)
{
	struct ssu_pirate blackbeard = {950, 48, "Edward Teach"}, pirate;
	char *fname = "ssu_data";
	FILE *fp1, *fp2;

	// 쓰기전용으로 파일 오픈, 파일이 없으면 생성
	if ((fp2 = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	// 구조체의 데이터를 파일에 쓰기
	if (fwrite(&blackbeard, sizeof(struct ssu_pirate), 1, fp2) != 1)
	{
		fprintf(stderr, "fwrite error\n");
		exit(1);
	}

	// 파일 닫을 시 에러 발생 확인
	if (fclose(fp2)) {
		fprintf(stderr, "fclose error\n");
		exit(1);
	}

	// 파일을 읽기 전용으로 다시 오픈
	if ((fp1 = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	// 파일에서 읽어온 데이터를 구조체 변수에 저장
	if (fread(&pirate, sizeof(struct ssu_pirate), 1, fp1) != 1)
	{
		fprintf(stderr, "fread error\n");
		exit(1);
	}

	if (fclose(fp1)) {
		fprintf(stderr, "fclose error\n");
		exit(1);
	}

	// 읽어온 데이터 출력
	printf("name=\"%s\" booty=%lu beard_length=%u\n", pirate.name, pirate.booty, pirate.beard_length);
	exit(0);
}
